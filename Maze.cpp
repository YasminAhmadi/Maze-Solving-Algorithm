#include <iostream>
using namespace std;
//#include <climits>

#define INTMAX 2147483647
  
//number of vertices in the graph
int V;
int m;
int n;
int v=0;
//the numbers could be larger than 9999 based off test cases (in case of a runtime error)
int graph[9999][9999];
int g[9999][9999];
int s=0;
int indexi=0;
int indexj=0;
int dd;
int minn=INTMAX;
int minni;
bool torf;
int countt=0;
int countarr[9999];

//find the number of vertices in the graph -> V
void number(){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]!=0)
                v++;
        }
    }
}
//creates the adjacency matrix (which is VxV) and sets all the vertices to 0
void starter(){
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j]=0;
        }
    }
}
//finds the ordinal position of vertex (ii,jj) in the maze
int find(int ii,int jj){
    int c=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i==ii && j==jj)
                return c;
            if(g[i][j]!=0)
                c++;
        }
    }
    return c;
}
//finds the i and j (stored in indexi and indexj) of the (cc)th vertex in the maze
void findij (int cc){
    int c=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(g[i][j]!=0)
                c++;
            if(c == cc){
                indexi=i;
                indexj=j;
                return;
            }
        }
    }
    return;
}

//inserts proper values in the adjacency matrix based off the grid(maze)
void complete(){
    for(int i=0;i<v;i++){
        findij(i+1);
        if(g[indexi-1][indexj]!=0 && i!=0){
            int c;
            c=find(indexi-1,indexj);
            //c now shows the ordinal position of vertex i is in the maze which will be the row of that vertex
            //in the adjacency graph
            graph[c][i]=g[indexi][indexj];
            graph[i][c]=g[indexi-1][indexj];
        }
        if(g[indexi][indexj-1]!=0 && i!=v-1){
                  int c;
                 c=find(indexi,indexj-1);
                  graph[c][i]=g[indexi][indexj];
                  graph[i][c]=g[indexi][indexj-1];
       }
    }
    //the adjacency matrix got created
    /*cout<<endl;
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }*/
}
void findij2 (int cc){
    int c=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            
            if(g[i][j]!=0){
                c++;
            }
            if(c == cc){
                indexi=i;
                indexj=j;
                return;
            }
        }
    }
    return;
}


//Btree is used in the dijkstra function below
class btreenode
{
    public:
    //array to store the keys of each node
    int *keys;
    //array to store the datas of each node
    int *datas;
    //array to store the flags of each node
    bool *flags;
    //array to store the availabilities of each node
    bool *avail;
    int deg;
    btreenode **child;
    int number;
    bool l;
    //true if the node is a leaf

    btreenode(int d, bool leaf1){
          deg = d;
          l = leaf1;
          number = 0;
          int ddd=deg*2;
          //can have maximum 2*degree-1 keys/datas/...
          keys = new int[ddd-1];
          datas = new int[ddd-1];
          flags = new bool[ddd-1];
          avail = new bool[ddd-1];
          //can have maximum 2*degree children
          child = new btreenode *[ddd];
          //we start with zero keys
    }
    void trueorfalse(int k){
          //There are n keys and n+1 children
          //going through all the n keys
          int i;
          for (i=0;i<number;i++){
              if (l == false){
                  //if the node is not a leaf, go through the tree with this node as its root
                  child[i]->trueorfalse(k);
              }
              //if we found the key -> set torf = flag
              if(keys[i] == k){
                  if(flags[i]==true)
                      torf=true;
                  else
                      torf=false;
                  return;
              }
          }
          if (l == false)
              child[i]->trueorfalse(k);
    }
    void setflag(int k,int i){
         //as we did before:
           int ii;
           for (ii=0;ii<number;ii++){
               if (l == false)
                   child[ii]->setflag(k,i);
               if (keys[ii] == k && avail[ii]==true){
                      //if the found key== k, set its flag to true (if ii==1) or false (if ii==0)
                      flags[ii]=i;
                      return;
                  }
           }
           if (l == false)
               child[ii]->setflag(k,i);
    }
    //find the minimum and set minni to its index
    void findminindex(){
          //as we did before:
          int i;
          for (i=0;i<number;i++){
              if (l == false)
                  child[i]->findminindex();
              //we find the minimum among the ones that are available (avail[i]==true) and flag==false
              if(datas[i]<=minn && flags[i]==false && avail[i]==true){
                  minn=datas[i];
                  minni=keys[i];
              }
          }
          if (l == false)
              child[i]->findminindex();
    }
    void getdata(int k){
          //as we did before:
          int i;
          for (i=0;i<number;i++)
          {
              if (l == false)
                  child[i]->getdata(k);
              //if we find the key and its available (the last updated one) return its data
              if(keys[i] == k && avail[i]==true){
                  dd=datas[i];
                  return;
              }
          }
          if (l == false)
              child[i]->getdata(k);
    }
    void findthenfalse(int k){
          //as we did before:
          int i;
          for (i=0;i<number;i++){
              if (l == false)
                  child[i]->findthenfalse(k);
              //if we find the key, set its availability to false so we will no longer use it
              if(keys[i] == k){
                  avail[i]=false;
                  return;
              }
          }
          if (l == false)
              child[i]->findthenfalse(k);
    }
    void insert(int k,int d){
          //start exploring from the rightmost vertex
            int i = number-1;
            // If this is a leaf node
            if (l == true){
                //we start from the rightmost one and and as long as the keys are larger than the given key (k) we
                //know they belong to the right of (k) so we move them all one vertex to the right so will end up
                //with an empty spot for (k)
                while (i >= 0 && keys[i] > k){
                    keys[i+1] = keys[i];
                    datas[i+1] = datas[i];
                    flags[i+1] = flags[i];
                    avail[i+1] = avail[i];
                    i--;
                }
                //if we're out of the loop it means the keys were no longer larger than (k) so this is the spot to
                //insert it into + there's an empty(!) spot for it to be inserted in
                keys[i+1] = k;
                datas[i+1] = d;
                flags[i+1] = false;
                //for now it is available
                avail[i+1] = true;
                //one other key added
                number = number+1;
            }
            //we always add to leaf, so if it is not, then we msut find the leaf -> by exploring through the children
            else
            {
                //Finding the right child to add to
                while (i>= 0 && keys[i]>k){
                    i--;
                }
                //if the child is full
                if (child[i+1]->number == 2*deg-1){
                    splitting(i+1, child[i+1]);
                    
                    //now the new parent is the key in the middle and the rest will be its children
                    if (keys[i+1]<k)
                        i++;
                    //now we found the split child which we're going to add to and it's not full anymore
                }
                child[i+1]->insert(k,d);
            }
      }

      void splitting(int i, btreenode *p){
          //splitting p, so creating a new node q from p
            btreenode *q=new btreenode(p->deg, p->l);
            //has degree-1 keys
            q->number = deg - 1;
          
            //copying (degree -1 ) keys/datas/flags/availabilities from the end of p to the new node
            for (int j = 0; j < deg-1; j++){
                q->keys[j] = p->keys[j+deg];
                q->datas[j] = p->datas[j+deg];
                q->flags[j] = p->flags[j+deg];
                q->avail[j] = p->avail[j+deg];
            }
          
            //also if p is not a leaf then it has children that must also be added to the new node
            if (p->l == false){
                for (int j=0;j<deg;j++){
                    q->child[j]=p->child[j+deg];
                }
            }
            //now the number of keys in p is acceptable (degree-1)
            p->number = deg - 1;
          
            //we move vertices to the right to empty up space for new child
           for (int j = number; j >= i+1; j--){
                child[j+1] = child[j];
           }
            //now we can add the new child
            child[i+1]=q;
          
            //we move all the keys/datas/... one place to the right until we find the suitable location so it can be added there
            for (int j = number-1; j >= i; j--){
                keys[j+1] = keys[j];
                datas[j+1] = datas[j];
                flags[j+1] = flags[j];
                avail[j+1] = avail[j];
            }
            //this node must be the middle key
            keys[i] = p->keys[deg-1];
            datas[i] = p->datas[deg-1];
            flags[i] = p->flags[deg-1];
            avail[i] = p->avail[deg-1];
            //now we have one vertex more
            number = number + 1;
      }
};

btreenode *root;
//degree of B-tree could be set to anything and it would still work fine
int deg=3;

void add(int k,int d){
    //if we've added this node before we have to make sure we remove the prev one simply by setting availability to false
    //(avail[i] -> false)
    //findthenfalse2(k);
    if (root != NULL){
        root->findthenfalse(k);}
    //if tree is empty
    if (root == NULL)
    {
        //create the new node and set it equal to root (since there is only one node it is a leaf (=> true)
        root = new btreenode(deg, true);
        //set key
        root->keys[0] = k;
        //set data
        root->datas[0] = d;
        //set flag
        root->flags[0] = false;
        //set availability
        root->avail[0] = true;  //it's available until the value gets updated( => availability -> false and a new node with the
        //same key gets created)
        root->number=1;  //since the tree was empty current number of keys -> 1
    }
    //if tree is not empty
    else
    {
        //if root is not full -> doesn't have (2*degree)-1 keys yet
        if (root->number!=2*deg-1)
        {
            root->insert(k,d);
           
        }
        //if root is full -> has (2*degree)-1 keys
        else {
                   btreenode *aaa = new btreenode(deg, false);
                   //the old root is not a root anymore, create a new root with the old root as its child
                   aaa->child[0] = root;
                   //but since the child (old root) is full, we need to split it
                   aaa->splitting(0, root);
                   //since the child got split we have to add another child to the new root, in order to know where to add:
                   int keycount=0;
                   if (aaa->keys[0] < k){
                       keycount++;
                   }
                   aaa->child[keycount]->insert(k,d);
         
                   // Change root
                   root=aaa;
            
        }
    }
}


  
//this function helps us store the path in countarr
void setpath(int parent[], int iii){
    //if j is the source we're done
    if (parent[iii] == - 1)
        return;
    setpath(parent, parent[iii]);
    //storing the path in countarr
    countarr[countt]=iii;
    countt++;
}
  
  
void dijkstra(int src){
    int parent[V];
    //all the vertices in the maze will be added as nodes to the B tree and their flags will be true if
    //the respective vertex is included in the shortest path tree
    
    //according to dijkstra we set all distances to INTMAX and flags as false in the beginning
    for (int i = 0; i < V; i++){
        parent[i] = -1;
        add(i,INTMAX);
    }
    //except the source, which distance has to be set to 0 so it will start from there
    //therefore we update the vertex 0 (which is the source) by simply adding it again ( the add function
    //will set the previous added node's availability to false so the old one will be out of use
    add(0,0);
    
    //now finding the shortest path
    for (int count = 0; count < V - 1; count++){
        //finding the minimum distance vertex from the ones we haven't gone through yet
        //first time: min index(minni) == source
        minn=INTMAX;
        if (root != NULL){
            root->findminindex();
        }
        //set the flag -> true for the chosen vertex (minimum) so we know its been picked out already
        //becuase we find the minimum only among the ones with false flags
        if (root != NULL){
            root->setflag(minni,1);
        }
        //a.showflag(u);
  
        for (int q=0;q<V; q++){
            //if the flag is true sets torf's value to 1 and vice versa
            if (root != NULL){
                root->trueorfalse(q);
            }
            if (root != NULL){
                root->getdata(minni);
            }
            //uu -> stores the data of minimum
            int uu=dd;
            if (root != NULL){
                root->getdata(q);
            }
            //the data of j is stored in dd
            
            //torf == false -> it's false, when the flag is false meaning it has not been processed yet
            //graph[minni][q] -> checks to see whether q and minni are actually connected or not
            //uu+graph[minni][q]<dd -> if the path through minimum is shorter than what we have now
            if ( (torf==false) && graph[minni][q] && uu+graph[minni][q]<dd){
                //cout<<endl<<"v: "<<v<<" parent: "<<u<<endl;
                parent[q] = minni;
                //find data of minimum -> will get stored in dd
                if (root != NULL){
                    root->getdata(minni);
                }
                add(q,dd + graph[minni][q]);
            }
        }
    }
    setpath(parent, V-1);
}
  

int main(){

    cin>>m>>n;
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>g[i][j];
        }
    }
    
    //these functions help us get an adjacency matrix (vxv) from the maze (mxn) we got as input
    //because the dijkstra function works on adjacency matrix and not on the actual maze
    number();
    starter();
    complete();
    //number of vertices in the maze
    V=v;
    //source is the (0)th vertex
    //end is the (V-1)th vertex
    dijkstra(0);
    int ccc=0;
    cout<<endl;
    
    //see the path
    /*for (int i = 0; i < n; i++)
      cout<< countarr[countt] <<" ";
      cout<<endl;*/
    
    
    //sorting countarr, which is the list that stores the nodes we have to traverse in order to get from source to end
    //storing helps us with turning proper nodes to -1, if it wasn't sorted we could pass a node and already print it then
    //figure out it was part of the path so we had to print it as -1 but it's already printed
    int i, j, min, temp;
      for (i = 0; i < countt - 1; i++) {
         min = i;
         for (j = i + 1; j < countt; j++)
         if (countarr[j] < countarr[min])
         min = j;
         temp = countarr[i];
         countarr[i] = countarr[min];
         countarr[min] = temp;
      }
    
    //the path is sorted (top left to bottom right) and not in order anymore
     // for (int i = 0; i < countt; i++)
      //cout<< countarr[i] <<" ";
    //cout<<endl<<endl;
    
    //find the place (i and j) of the first vertex on the given maze
    findij2(countarr[ccc]+1);
    /*for(int i=0;i<countt;i++)
        cout<<countarr[i]<<" ";*/
    //cout<<endl;
    
    //here we print the output
  bool first=true;
  for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            //if first == true -> it's the first vertex, it's the source and it's part of the path regardless
            if(first && g[i][j]!=0){
                cout<<"-1 ";
                first=false;
            }
            //indexi and indexj are the i and j of the vertices in our path
            //which are updated each time by giving the sorted elements of countarr as input to findij2
            else if (indexi==i && indexj==j){
                cout<<"-1 ";
                if(ccc<countt){
                //we move on to the next vertex of path and find its location in the maze and print -1 instead in that loc
                ccc++;
                findij2(countarr[ccc]+1);
                }
            }
            else
                cout<<" "<<g[i][j]<<" "; //this element is not part of the path, just print it normally
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}
