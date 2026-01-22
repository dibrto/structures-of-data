#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
using namespace std;

//(key, value) pair
template <typename K, typename V>
class Pair {
    public:
        Pair(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }

        const K& getKey() const   { return _key; }     // Get key
        void setKey(const K& k)   { _key = k; }        // Set key

        const V& getValue() const { return _value; }   // Get value
        void setValue(const V& v) { _value = v; }      // Set value
    private:
        K _key;                     // Key
        V _value;                   // Valuee
};

// Comparator
class HComp {
public:
    int operator()(const int& i) const
    { return i; }
};

template <typename K, typename V, typename H>
class HashMap {
    public:
        typedef Pair<const K,V> Entry; //(key,value) pair
        class Iterator;                // Iterator
    public:
        HashMap(int capacity = 100) : n(0), B(capacity) { } // Constructor
        int size() const { return n; }             // Number of entries
        bool empty() const { return size() == 0; } // Is the map empty?
        void erase(const Iterator& p) {eraser(p);} // Remove entry at position p
        void print();

        void erase(const K& k);                    // Remove entry with key k
        Iterator find(const K& k){        // Find key
            Iterator p = finder(k);
            if(endOfBkt(p))
                return end();
            else
                return p;
        }             

        Iterator put(const K& k, const V& v){       // Insert/replace (k,v)
            Iterator p = finder(k);
            if(endOfBkt(p))
                return inserter(p, Entry(k, v));
            else{
                p.ent->setValue(v);
                return p;
            }
        }

        Iterator begin(){      // Iterator to first entry
            if(empty())
                return end();
            BItor bkt = B.begin();
            while(bkt->empty())
                bkt++;
            return Iterator(B, bkt, bkt->begin());
        }
        
        Iterator end(){    // Iterator to end entry
            return Iterator(B, B.end());
        }                            

    protected:
        typedef list<Entry> Bucket;                // Bucket of entries
        typedef vector<Bucket> BktArray;           // Bucket array
        typedef typename Bucket::iterator EItor;   // Entry iterator
        typedef typename BktArray::iterator BItor; // Bucket iterator
        void nextEntry(Iterator& p) { ++p.ent; }   // Bucket s next entry
        bool endOfBkt(const Iterator& p)           // End of bucket
        { return p.ent == p.bkt->end(); }

        Iterator finder(const K& k){        // Find utility
            int i = hash(k) % B.size();
            BItor bkt = B.begin() + i;
            Iterator p(B, bkt, bkt->begin());
            while(!endOfBkt(p) && (*p).getKey() != k)
                nextEntry(p);
            return p;
        }
        Iterator inserter(const Iterator& p, const Entry& e){      // Insert utility
            EItor ins = p.bkt->insert(p.ent, e);
            n++;
            return Iterator(B, p.bkt, ins);
        }

        void eraser(const Iterator& p){     // Remove utility
            p.bkt->erase(p.ent);
            n--;
        }

    private:
        int n;       // Number of entries
        H hash;      // The hash comparator
        BktArray B;  // Bucket array
    public:
        class Iterator {
            private:
                EItor ent;                // Which entry
                BItor bkt;                // Which bucket
                const BktArray* ba;       // Which bucket array
            public:
                Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
                : ent(q), bkt(b), ba(&a) { }

                Entry& operator*() const{        // Get entry
                    return *ent;
                }             
                bool operator==(const Iterator& p) const{        // Are the iterators equal?
                    if(ba != p.ba || bkt != p.bkt){
                        return false;
                    } 
                    else if (bkt == bkt->end())
                        return true;
                    else  
                        return (ent == p.ent);
                }

                Iterator& operator++(){      // Next entry
                    ++ent;
                    
                    if(endOfBkt(*this)){
                        ++bkt;

                        while(bkt != ba->end() && bkt->empty())
                            ++bkt;

                        if(bkt == ba->end())
                            return *this;

                        ent = bkt->begin();
                    }
                        return *this;
                }      
                friend class HashMap;                     // Give HashMap access
        };
};



template <typename K, typename V, typename H>
void HashMap<K,V,H>::print()
{
    cout<<setw(5)<<"Keys"<<setw(13)<<"Values"<<endl;
    for(int i = 1; i<=size(); i++)
    {
        BItor bkt = B.begin() + i;
        Iterator p(B, bkt, bkt->begin());
        while (!endOfBkt(p))
        {
            int out = 12;
            if(i>9)
                out = 11;
            cout<<"Key: "<<(*p).getKey()<<setw(out)<<"Value: "<<(*p).getValue()<<endl;
            nextEntry(p);
        }
    }
}