#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue> 

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::queue;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef vector<string> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */


struct Node
{
    int len;
    string word;
    vector<string> chain;
};

bool differsByOneChar(string word1, string word2)
{
    int len = word2.length();
    int diff = 0;
    for(int i = 0; i< len; i++)
    {
        if(word1[i] != word2[i]) diff++;
    }

    if(diff == 1) {
        //cout << word1 << ":::::" << word2 << endl;
        return true;
    }
    else return false;
}

vector<string> nextWords(const Dictionary & dict, const string & from, const string & to, const vector<string> & used_words)
{   
    std::vector<string> words;
    for(auto i = dict.begin(); i != dict.end(); i++)
    {
        if(differsByOneChar(from,*i) && from != *i)
        {
           words.push_back(*i);
        } 
    }

    return words;
}

/*vector<Node> createGraph(const Dictionary & dict, string from , string to)
{   
    vector<Node> graph;
    vector<string> words;
    words.push_back(from);
    string previous;
    std::vector<string> used_words;

    bool done = false;
    while(!done)
    {
        if(std::find(words.begin(), words.end(),to) != words.end())done = true; // If word found

        //cout << "loop1" << endl;
        for(string word: words)
        {   
            //cout << "loop2" << endl;
            Node currNode = Node();
            currNode.edges = nextWords(dict,word,to,used_words);
            //if(graph.find(word) != graph.end())
            //{
              //  return graph;
            //}
            //cout << word << "!!!!" << endl;
            graph.push_back(currNode);
        }
        
        std::vector<string> newWords;
        for(int i = 0; i< words.size(); i++)
        {   
            previous = words[0];
            //cout << words[i] << endl;
            std::vector<string> v;
            v = nextWords(dict,words[i],to,used_words);
            for(string str : v)
            {
                newWords.push_back(str);
                used_words.push_back(str);
            }
        }
        words = newWords;
    }

    cout << "GRAPH CREATED!!" << endl;
    return graph;
}*/




bool includeString(vector<string> vec, string str)
{
    for(string s : vec)
    {
        if(s == str) return true;
    }

    return false;
}

void print_graph(map<string,Node> graph)
{   

    for(auto i = graph.begin();i != graph.end(); i++)
    {
        //cout << i->first['aula'] << " ¤¤¤" << endl;
        //for(string s : i->second.edges)
        //{
       //     cout << "Edge: " << s << endl;
       // }
    }
}
vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    vector<string> i_vec;
    i_vec.push_back(from);
    queue<Node> Q;
    Node item = {1,from,i_vec};
    Q.push(item);

    while(!Q.empty())
    {
        Node curr = Q.front(); Q.pop();

        for(auto i = dict.begin(); i != dict.end(); i++)
        {   
            string temp = *i;
            if(differsByOneChar(curr.word,temp))
            {
                item.word = temp;
                item.len = curr.len + 1;
                item.chain = curr.chain;
                item.chain.push_back(item.word);
                Q.push(item);

                if(temp == to)
                {
                    return item.chain;
                }
            }
        }
    }

}



/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result;

    
}


/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
vector<string> read_dictionary() {
    string line;
    vector<string> result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.push_back(line);
    }

    return result;
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}


/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            if (chain.size() == 1) {
                cout << "ingen lösning" << endl;
            } else {
                cout << chain.size() << " ord" << endl;
                print_chain(chain);
            }
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": " << chain.size() << " ord" << endl;
            print_chain(chain);
        }
    }
}

int main() {
    vector<string> dict = read_dictionary();
    read_questions(dict);

    return 0;
}
