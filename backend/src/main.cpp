#include <iostream>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <queue>
#include <mmsystem.h>

using namespace std;

class TreeNode;         
class tree;
class Tree2;
/*Details class contains information for each songs*/
class details
{
public:
    string name;
    string artist;
    string fileName;
  
    bool equality(details d)
    {
        if (name == d.name && artist == d.artist && fileName == d.fileName)
            return true;
        else
            return false;
    }
   
    void addDetails(string n, string a, string f)
    {
        name = n;
        artist = a;
        fileName = f;
    }
    // Add song names to the bst for future uses
    void addDetails(TreeNode *, Tree2);
  
    void printDetails()
    {
        cout << "Name of song: " << name << endl;
        cout << "Name of artist: " << artist << endl;
        cout << "Name of file: " << fileName << endl;
    }
    
    string returnFileName()
    {
        return fileName;
    }
    string returnSongName()
    {
        return name;
    }
    string returnArtistName()
    {
        return artist;
    }
};

/* TreeNode class contains the basic structure of the BST implemented in the code*/

// class TreeNode
// {
// public:
//     string name;
//     TreeNode *left, *right;
  
//     TreeNode()
//     {
//         name = "";
//         left = NULL;
//         right = NULL;
//     }
    
//     TreeNode(string s)
//     {
//         name = s;
//         left = NULL;
//         right = NULL;
//     }
// };


class TreeNode {
public:
    string name;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(string val) {
        name = val;
        left = right = NULL;
        height = 1;
    }
};

class Tree2 {
private:
    TreeNode* root;

    int get_height(TreeNode* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int balance_factor(TreeNode* node) {
        if (node == NULL) return 0;
        return get_height(node->left) - get_height(node->right);
    }

    TreeNode* rot_right(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(get_height(y->left), get_height(y->right));
        x->height = 1 + max(get_height(x->left), get_height(x->right));

        return x;
    }

    TreeNode* rot_left(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(get_height(x->left), get_height(x->right));
        y->height = 1 + max(get_height(y->left), get_height(y->right));

        return y;
    }

    TreeNode* insert_rec(TreeNode* node, string name) {
        if (node == NULL) {
            return new TreeNode(name);
        }

        if (name < node->name) {
            node->left = insert_rec(node->left, name);
        } else if (name > node->name) {
            node->right = insert_rec(node->right, name);
        } else {
            return node;
        }

        node->height = 1 + max(get_height(node->left), get_height(node->right));

        int balance = balance_factor(node);


        if (balance > 1 && name < node->left->name) {
            return rot_right(node);
        }

        if (balance < -1 && name > node->right->name) {
            return rot_left(node);
        }

        if (balance > 1 && name > node->left->name) {
            node->left = rot_left(node->left);
            return rot_right(node);
        }

        if (balance < -1 && name < node->right->name) {
            node->right = rot_right(node->right);
            return rot_left(node);
        }

        return node;
    }

public:
    Tree2() {
        root = NULL;
    }

    void insertIntoAVL(string name) {
        root = insert_rec(root, name);
    }

    void display() {
        if (root == NULL) {
            cout << "Empty!!!" << endl;
            return;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            cout << node->name << "\n";
            
            if (node->left != NULL)
                q.push(node->left);
            
            if (node->right != NULL)
                q.push(node->right);
        }
        cout << endl;
    }

    int searchnplay(string name, details* d) {
        TreeNode* temp = root;
        
        while (temp != NULL) {
            if (temp->name == name) {
                return getindex(d, name);
            } else if (name < temp->name) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        
        cout << "Not found in our library!!" << endl;
        return -1;
    }

    int getindex(details* d, string name) {
        for (int i = 0; i < 10; i++) {
            if (d[i].name == name) {
                return i;
            }
        }
            return -1;
    }
}avl;

/* tree class contains all related functions for BST implementation */

class tree
{
public:
    TreeNode *root;
    // default constructor of tree
    tree()
    {
        root = NULL;
    }
    // function to insert song names into BST
    void insertIntoBST(string name)
    {
        // if tree is empty initialise new node with root
        if (root == NULL)
        {
            TreeNode *t = new TreeNode(name);
            root = t;
            return;
        }
      
        TreeNode *curr = root;
        while (true)
        {
            // traverse the left sub-tree
            if (name < (curr->name))
            {
                if (curr->left)
                    curr = curr->left;
                else
                {
                    curr->left = new TreeNode(name);
                    break;
                }
            }
            // traverse the right sub-tree
            else
            {
                if (curr->right)
                    curr = curr->right;
                else
                {
                    curr->right = new TreeNode(name);
                    break;
                }
            }
        }
    }
    /*display function to display node data of
    each node in level order */
    void display()
    {
        if (root == NULL)
        {
            cout << "Empty!!!" << endl;
            return;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();
            cout << node->name << "\n";
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
        cout << endl;
    }
    /*returns the index of the song
    to be searched using linear search algo*/
    int getindex(details *d, string name)
    {
        for (int i = 0; i < 10; i++)
        {
            if (d[i].name == name)
            {
                return i;
            }
        }
        return -1;
    }
    /*function to search the name of song in BST
    and call getindx to get and then return it
    to the driver code*/
    int searchnplay(string name, details *d)
    {
        TreeNode *temp = root;
        while (temp != NULL)
        {
            if (temp->name == name)
            {
                int idx = getindex(d, name);
                return idx;
            }
            else if (name < temp->name)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        cout << "Not found in our library!!" << endl;
        return -1;
    }
} bst; // global object of the tree


void details::addDetails(TreeNode *root, Tree2 t)
{
    t.insertIntoAVL(name);
}
// structure of each song
struct song
{
    details d;
    song *next;
    song *prev;
};
/* function to write songs into details array
and bst by reading from files */
bool writeSongs(details *d, Tree2 *avl)
{
    fstream database("nameartist.txt");
    fstream fileNames("mp3list.txt");
    string line, name, artist, file;
    char ch;
    unsigned int i, flag, j = 0;
    if (database.is_open() && fileNames.is_open())
    {
        while (!database.eof() && !fileNames.eof())
        {
            getline(database, line);
            getline(fileNames, file);
            name = "";
            artist = "";
            i = flag = 0;
            while (i < line.length())
            {
                ch = line[i];
                /*technique implemented to read file
                as name before encountering comma(,)
                and as artist after it*/
                if (ch == ',')
                {
                    flag = 1;
                    goto skipComma;
                }

                if (flag)
                    artist += ch;
                else
                    name += ch;
            skipComma:
                i++;
            }
            // bst insertion function calling
            avl->insertIntoAVL(name);
            // insertion in details array calling
            (d + j)->addDetails(name, artist, file);
            j++;
        }
        return true;
    }
    else
        return false;
}

/*function to play a song based on index
received from calling) wmc*/
void playSong(details d) {
    int n = 0;
    time_t t1, t2, previous_pause_time = 0;

    char buffer[128];
    string songPath = "songs\\" + d.returnFileName(); // Separate path construction
    string filename = "open \"" + songPath + "\" type mpegvideo alias mp3";

    // Check if file open was successful
    MCIERROR err = mciSendString(filename.c_str(), NULL, 0, NULL);
    if (err != 0) {
        mciGetErrorString(err, buffer, 128);
        cout << "MCI Error: " << buffer << endl;
        cout << "Attempted to open file: " << songPath << endl;
        return;
    }

    while (1) {
        t1 = time(0); // Record start time
        mciSendString("play mp3", NULL, 0, NULL);
        cout << "Playing song - " << d.returnSongName() << endl;
        cout << endl;
        cout << "Enter 1 to pause the song or 2 to end the song - " << endl;
        cin >> n;
        if (n == 1) {
            mciSendString("pause mp3", NULL, 0, NULL);
            t2 = time(0);
            cout << "Song paused after playing for " << t2 - t1 + previous_pause_time << " seconds.\n\n";
            previous_pause_time += t2 - t1;
            cout << "Enter 1 to resume the song or 2 to stop: ";
            cin >> n;

            if (n == 1) {
                t1 = time(0);
                mciSendString("play mp3", NULL, 0, NULL);
                cout << "Resuming song... \n";
            } else if (n == 2) {
                mciSendString("close mp3", NULL, 0, NULL);
                break;
            }
        } else if (n == 2) {
            mciSendString("close mp3", NULL, 0, NULL);
            break;
        }
    }
}
/* class songQueue maintains the queue of songs */
class songQueue
{
    song *head, *tail;

public:
  
    songQueue()
    {
        head = NULL;
        tail = NULL;
    }
   
    void addSong(details d)
    {
        song *s = new song;
        s->d = d;
        if (head == NULL)
        {
            head = s;
            tail = s;
            s->prev = NULL;
        }
        else
        {
            song *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = s;
            s->prev = temp;
            tail = tail->next;
        }
        s->next = NULL;
    }
  
    bool printSongByIndex(int x)
    {
        song *temp = head;
        for (int i = 0; i < x; i++)
            temp = temp->next;

        cout << "Song number " << x + 1 << " : " << endl;
        (temp->d).printDetails();
        cout << endl;

        return true;
    }
    void playQueueFromEnd(int i)
    {
        song *temp = tail;
        while (temp != head->prev)
        {
            printSongByIndex(i);
            i--;
            playSong(temp->d);
            temp = temp->prev;
        }
    }
    
    void playQueueFromFront()
    {
        song *temp = head;
        int j = 0;
        while (temp != tail->next)
        {
            printSongByIndex(j);
            j++;
            playSong(temp->d);
            temp = temp->next;
        }
    }
    // function to delete the queue
    void clearQueue()
    {
        song *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    song *retHead()
    {
        return head;
    }
    ~songQueue()
    {
        song *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};
/*class to maintain the playlist*/
class playlist
{
    song *head;

public:
    playlist()
    {
        head = NULL;
    }
    void addSong(details d)
    {
        song *s = new song;
        s->d = d;
        if (head == NULL)
        {
            head = s;
            s->prev = NULL;
        }
        else
        {
            song *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = s;
            s->prev = temp;
        }
        s->next = NULL;
    }
    // function to delete a song from the playlist
    bool delSong(details d)
    {
        int flag = 0;
        song *temp = head;
        if (d.equality(temp->d))
            goto skipWhile;
        while (temp->next != NULL)
        {
            if ((d.equality((temp->next)->d)))
            {
                flag = 1;
                break;
            }
            else
                temp = temp->next;
        }
    skipWhile:
        if (flag)
        {
            song *tbd = temp->next;
            temp->next = tbd->next;
            delete tbd;
            return true;
        }
        else
            return false;
    }
    // function to print the songs present in the playlist
    bool printSongs()
    {
        int i = 1;
        song *temp = head;
        while (temp != NULL)
        {
            cout << "Song number " << i << " : " << endl;
            (temp->d).printDetails();
            cout << endl;
            temp = temp->next;
            i++;
        }
        return true;
    }
    // search function for playlist
    bool searchSong(details d)
    {
        song *temp = head;
        while (temp != NULL)
        {
            if (temp->d.returnFileName() == d.returnFileName())
                return true;
            else
                temp = temp->next;
        }
        return false;
    }
    void playPlaylist()
    {
        song *temp = head;
        while (temp != NULL)
        {
            playSong(temp->d);
            temp = temp->next;
        }
    }
    ~playlist()
    {
        song *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

/*driver code*/

int main()
{
    details d[10];
    songQueue q;
    int ch, w = 0, opt = 1;
    int i = 0, x, y, z;
    playlist p[10];
    writeSongs(d, &avl);
    cout<<string(3, '\n');
    cout<<"Verse - Music streaming platform"<<string(2, '\n');
    cout << "SONGS IN LIBRARY: "<<"\n";
    avl.display();
    cout << endl;
    while (true)
    {
        cout << "1: Play Single Song" << endl;
        cout << "2: Add songs to Queue" << endl;
        cout << "3: Play queue" << endl;
        cout << "4: Create Playlist" << endl;
        cout << "5: Play existing Playlist" << endl;
        cout << "6: Search 'n play" << endl;
        cout << "7: Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch)
        {
        // Play Single Song
        case 1:
        {
            for (int x = 0; x < 5; x++)
            {
                cout << "Song number: " << x + 1 << endl;
                d[x].printDetails();
                cout << "\n";
            }
            int y;
            cout << "Enter song number to play: ";
            cin >> y;
            playSong(d[y - 1]);
            system("cls");
            break;
        }
        // Add songs to Queue
        case 2:
        {
            while (opt)
            {
                for (int x = 0; x < 5; x++)
                {
                    cout << "Song number: " << x + 1 << endl;
                    d[x].printDetails();
                    cout << "\n";
                }
                int y;
                cout << "Enter song number to add to queue: ";
                cin >> y;
                q.addSong(d[y - 1]);
                w++;
                cout << "Do you want to add another song [1(YES)/0(NO)]: ";
                cin >> opt;
            }
            system("cls");
            break;
        }
        // Play queue
        case 3:
        {
            if (q.retHead() == NULL)
            {
                cout << "No song in the queue \n";
                break;
            }
        replay:
            cout << "Play from beginning or end [1(BEGINNING)/0(END)]: ";
            cin >> opt;
            if (opt == 1)
                q.playQueueFromFront();
            else if (opt == 0)
                q.playQueueFromEnd(w - 1);
            else
            {
                cout << "Not a valid selection \n";
                goto replay;
            }

            q.clearQueue();
            system("cls");
            break;
        }
        // Create Playlist
        case 4:
        {
            if (i <= 9)
            {
                opt = 1;
                cout << "Play list name: Play list-" << i + 1 << "\n";
                while (opt != 0)
                {
                    for (x = 0; x < 5; x++)
                    {
                        cout << "Song number: " << x + 1 << endl;
                        d[x].printDetails();
                        cout << "\n";
                    }
                    cout << "Enter song number to add to play list: ";
                    cin >> y;
                    p[i].addSong(d[y - 1]);
                    cout << "Do you want to add another song(1/0): ";
                    cin >> opt;
                }
                i++;
            }
            else
                cout << "Maximum play list created!";
            break;
        }
        // Play existing Playlist
        case 5:
        {
            if (i == 0)
            {
                cout << "No play list to play yet!\n";
                break;
            }
            cout << "Enter the play list number to play: ";
            cin >> z;
            if (z > 10 || z > i)
            {
                cout << "Not a valid play list";
                break;
            }
            cout << "\n\n";
            p[z - 1].printSongs();
            p[z - 1].playPlaylist();
            break;
        }
        // Search 'n play
        case 6:
        {
            string name;
            cout << "Enter song name to search: ";
            getline(cin >> ws, name);
            int idx = avl.searchnplay(name, d);
            playSong(d[idx]);
            break;
        }
   
        case 7:
        {
            cout << "THANK YOU " << (char)1 << endl;
            exit(0);
        }
        default:
        {
            cout << "INVALID!!!!" << endl;
            break;
        }
        }
    }
    return 0;
}
