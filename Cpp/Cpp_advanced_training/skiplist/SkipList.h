#ifndef SKIP_LIST
#define SKIP_LIST
#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>

  extern "C" long random();

template <class Val, class Alloc=std::allocator<Val> >
class SkipNode {
public:

  const SkipNode<Val,Alloc>* next() const { return fwdNodes[0]; }
        SkipNode<Val,Alloc>* next()       { return fwdNodes[0]; }

  const Val& get() const { return val; }
        Val& get()       { return val; }

private:
  typename Alloc::rebind<SkipNode<Val,Alloc>* >::other node_ptr_allocator;

public:
  SkipNode **fwdNodes;
  int nodeHeight;

  Val val;

  void destroy()
  {
    node_ptr_allocator.deallocate(fwdNodes, nodeHeight);
  }

  ~SkipNode()
  {
    destroy();
  }

  SkipNode(int h, Val o=Val()) : 
    nodeHeight(h), val(o)
  {
    fwdNodes = node_ptr_allocator.allocate(h);
    for ( int x = 0; x < nodeHeight; x++ )
      fwdNodes[x] = 0;
  }

  int getHgt(void) const
  {
    return nodeHeight;
  }

  void resize(int newlvl) {
    SkipNode<Val,Alloc>** tmpVec;

    tmpVec=node_ptr_allocator.allocate(newlvl);
    copy(fwdNodes, fwdNodes+nodeHeight, tmpVec);
    node_ptr_allocator.deallocate(fwdNodes, 1);
    fwdNodes=tmpVec;
    nodeHeight=newlvl;
  }

};


template <class Key, class Obj, class Alloc = std::allocator<std::pair<Key, Obj> > >
class SkipList {
public:

  typedef std::pair<Key, Obj> ValType;
  typedef SkipNode<ValType, Alloc> NodeType;

  SkipList() : curHeight(1), nItems(0)
  {

    // Create head and tail and attach them
    head = node_allocator.allocate(1);
    tail = node_allocator.allocate(1);
    head = new (head) NodeType (curHeight);
    tail = new (tail) NodeType (curHeight);
    updateVec = node_ptr_allocator.allocate(curHeight);

    for ( int i = 0; i < curHeight; i++ ) {
	head->fwdNodes[i] = tail;
	tail->fwdNodes[i] = 0;
    }
  }

  ~SkipList()
  {
    // Walk 0 level nodes and delete all
    NodeType* tmp;
    NodeType* nxt;
    tmp = head;

    while ( tmp )
    {
      nxt = tmp->fwdNodes[0];
      tmp->destroy();
      node_allocator.deallocate(tmp, 1);
      tmp = nxt;
    }
  }

  int 
  newLevel()
  {
    int tmpLvl = 1;
    // Develop a random number from 1 upto curHeight (node height).
    while ((random() & 1) && tmpLvl < curHeight)
      tmpLvl++;

    return tmpLvl;
  }

  bool insert(const ValType& o) {
    insert(o.first, o.second);
  }

  bool insert(const Key& k, const Obj& o)
  {
    
    NodeType* tmp;

    // Figure out where new node goes
    tmp=findIt(k);

    if ( tmp!=tail && tmp->get().first == k )
    {
    // If dup, return false
      return false;
    }
    else 
    {
      do_insert(k, o);
    }
    return true;
  }

  NodeType* end() { return tail; }

  const NodeType* end() const { return tail; }

  NodeType* begin() { return head->fwdNodes[0]; }

  const NodeType* begin() const { return head->fwdNodes[0]; }

  NodeType* find(const Key& k)
  {
    return findIt(k);
  }

  const NodeType* find(const Key& k) const
  {
    SkipList *p=const_cast<SkipList *>(this);
    return p->findIt(k);
  }

  bool remove(const Key& k)
  {
    NodeType* tmp;

    // Find the node we need to delete
    tmp=findIt(k);

    if ( tmp!=tail && tmp->get().first == k )
    {
      for ( int i = 0; i < curHeight; i++ )
      {

	if ( updateVec[i]->fwdNodes[i] != tmp ) 
	  break;
	updateVec[i]->fwdNodes[i] = tmp->fwdNodes[i];
      }

      tmp->destroy();
      node_allocator.deallocate(tmp, 1);

      while ( ( curHeight > 1 ) &&
	    ( ( head->fwdNodes[curHeight] == tail ) ) ) {
	curHeight--;
      }

      --nItems;
      return true;

    }
    else
    {
      return false;
    }
  }

  const Obj& operator[](const Key& k) const
  {
    const NodeType* tmp;

    // Find the key and return the node
    tmp=findIt(k);

    if ( tmp!=tail && tmp->get().first == k )
      return tmp->get().second;
    else
      return Obj();
  }

  Obj& operator[](const Key& k)
  {
    NodeType* tmp;

    // Find the key and return the node
    tmp=findIt(k);

    if ( tmp!=tail && tmp->get().first == k )
      return tmp->get().second;
    else
      return do_insert(k, Obj())->get().second;
  }

  size_t size() {
    return nItems;
  }

  void dump(std::ostream& of) const
  {
    NodeType* tmp;

    tmp = head;
    of << "curHeight: " << curHeight << endl;

    while ( tmp != tail )
    {
      of << (void *) tmp << ' ' << tmp->getHgt() << ' ';
      if ( tmp == head ) {
	of << "head" << endl;

      } else {
	of << '(' << tmp->get().first << "," << tmp->get().second << ")" << endl;
      }

      for (int i=0; i<tmp->getHgt(); i++) of << (void *) tmp->fwdNodes[i] << ' ';
      of << endl;
      tmp = tmp->fwdNodes[0];
    }

    of << "tail" << endl;
    for (int i=0; i<tmp->getHgt(); i++) of << (void *) tmp->fwdNodes[i] << ' ';
    of << endl;
  }

private:
  NodeType* findIt(const Key& k)
  {

    // Find the key and return the node

    NodeType* tmp=head;
    for (int h = curHeight-1; h >= 0; h-- )
    {
      NodeType* nxt=tmp->fwdNodes[h];

      while ( nxt != tail && nxt->get().first < k )
      {
        tmp = nxt;
        nxt = tmp->fwdNodes[h];
      }

      updateVec[h] = tmp;
    }
    tmp = tmp->fwdNodes[0];
    return tmp;
  }

  void resize(int newHeight) {

      head->resize(newHeight);
      tail->resize(newHeight);

      NodeType** tmpVec;
      tmpVec=node_ptr_allocator.allocate(newHeight);
      copy(updateVec, updateVec+curHeight, tmpVec);
      node_ptr_allocator.deallocate(updateVec, 1);
      updateVec=tmpVec;

      head->fwdNodes[curHeight] = tail;
      tail->fwdNodes[curHeight] = 0;
      updateVec[curHeight] = head;

      curHeight=newHeight;
  }

  NodeType* do_insert(const Key& k, const Obj& o) {
    // Perform an insert

    NodeType* tmp;
    int lvl = newLevel();

    if ( lvl == curHeight ) {
      resize(lvl+1);
    }

    // create new element
    tmp = node_allocator.allocate(1);
    tmp = new (tmp) NodeType(lvl, make_pair(k, o));

    // and insert it
    for ( int i = 0; i < lvl; i++ )
    {
      tmp->fwdNodes[i] = updateVec[i]->fwdNodes[i];
      updateVec[i]->fwdNodes[i] = tmp;
    }
    ++nItems;
    return tmp;
  }

  typename Alloc::rebind<NodeType* >::other node_ptr_allocator;
  typename Alloc::rebind<NodeType >::other node_allocator;

  NodeType* head;
  NodeType* tail;
  NodeType** updateVec;

  int curHeight;
  size_t nItems;

};
#endif //SKIP_LIST
