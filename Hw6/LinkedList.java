import java.util.*;
@SuppressWarnings("unchecked")
public class LinkedList<E> implements Queue<E>,List<E> {
	private E linkedlist[];
	private int size;
	
	@Override 
	public int size(){//Returns Size
		return size;
	}

	/**Constuctor*/
	public LinkedList(){//Constructor
		size=0;
		linkedlist= (E[]) new Object[1];
	}
	
	@Override
	public void add(E e){//Adds an Element as a Last Element
		E trash[];
		trash=(E[]) new Object[size+1];
		if (size>0) {
			for (int i=0;i<size() ;i++ )
				trash[i]=linkedlist[i];
		}
		linkedlist=(E[]) new Object[size+1];
		for (int i=0;i<size() ;i++ )
			linkedlist[i]=trash[i];

		linkedlist[size]=e;
		size++;
	}

	@Override
	public void clear(){//Clears All Elements
		size=0;
		linkedlist= (E[]) new Object[1];
	}
	
	@Override
	public boolean contains(E e){//Checks For an Element
		for (int i=0;i<this.size();i++ ) 
			if (linkedlist[i]==(e))
				return true;
		return false;
	}
	
	@Override
	public boolean isEmpty(){//Returns True If There Is No Element
		if (this.size()==0){
			return true;
		}else
			return false;
	}
	
	@Override
	public void remove(E e){//Removes An Element 
		Iterator_C iter = this.iterator();
		for (int i= 0 ;i<size;i++) {
			if (linkedlist[i]==e){
				for(int j= i ;j<size-1;j++){
					linkedlist[j]=linkedlist[j+1];
				}
				linkedlist[size-1]=null;
				size--;i--;
				//return;
			}
		}
	}

	@Override
	public void addAll(Collection c){//Adds The Elements of Other Collection
		Iterator_C iter = c.iterator();
     	while(iter.hasNext())
      		this.add((E)iter.next());
	}
	
	@Override
	public boolean containsAll(Collection c){//Checks The Existence of Collection
		int counter=0;
		Iterator_C iter = c.iterator();

		while(iter.hasNext())
			if (this.contains((E)iter.next()))
				counter ++;
	
	    if (counter != c.size())
			return false;
        return true;
	}

	@Override
	public void removeAll(Collection c){//Removes All Common Elements
		Iterator_C iter = c.iterator();
		while(iter.hasNext())
			this.remove((E)iter.next());
	}

	@Override
	public void retainAll(Collection c){//Removes Except Common Elements
		E[] trash;
		trash= (E[]) new Object[c.size()];
		Iterator_C iter = c.iterator();
		int counter=0;
		
		while(iter.hasNext()) {
			E temp=(E)iter.next();
			if (this.contains(temp)) {
				trash[counter]=temp;
				counter++;
			}
		}
		this.clear();
		for (int i =0 ;i<counter ;i++ )
			this.add(trash[i]);
	}
	
	@Override
	public Iterator_C iterator(){//Returns The Iterator Of LinkedList
		Iterator_C temp = new Iterator_C(this,linkedlist);
		return temp;
	}

	/**Returns The Head Of Queue or Throws Exception, If There Is No Element */
	@Override
	public E element()throws Exception{
		if(this.size() > 0)
		{
			E temp=linkedlist[0];
			return temp;
		}else
			throw new Exception("Empty");
	}

	/** Adds An Element*/
	@Override
	public void offer(E e){
		this.add(e);
	}

	/**Returns And Removes The Head Of Queue or Throws Exception, If There Is No Element*/
	@Override
	public E poll()throws Exception{
		if(this.size() > 0)
		{
			E temp=linkedlist[0];
			this.remove(linkedlist[0]);
			return temp;
		}else
			throw new Exception("Empty");
	}

	/**Prints All Elements*/
	public void printAllElements(){ 
		Iterator_C iter = this.iterator();
		while (iter.hasNext())
			System.out.print((E)iter.next()+" ");
		
		System.out.println();
	}
}