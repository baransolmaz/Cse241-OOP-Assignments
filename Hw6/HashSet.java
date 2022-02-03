import java.util.*;
@SuppressWarnings("unchecked")
public class HashSet<E> implements Set<E> {
	private E hash[];
	private int size; 
	
	@Override
	public int size(){//Returns The Size
		return size;
	}
	/**Constructor*/
	public HashSet(){
		size=0;
		hash= (E[]) new Object[1];
	}

	@Override 
	public void add(E e){//Adds The Element
		E trash[];
		trash=(E[]) new Object[size+1];
		if (size>0) {
			for (int i=0;i<size ;i++ ) 
				if (this.contains(e))return;
			
			for (int i=0;i<size ;i++ )
				trash[i]=hash[i];
		}
		hash=(E[]) new Object[size+1];
		for (int i=0;i<size ;i++ )
			hash[i]=trash[i];

		hash[size]=e;
		size++;
	}

	@Override
	public boolean contains(E e){//Checks The Existence of an Element
		for (int i=0;i<this.size();i++ ) 
			if (hash[i]==(e))
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
	public void clear(){//Clears Set
		size=0;
		hash= (E[]) new Object[1];
	}

	@Override
	public void remove(E e){//Removes An Element
		try{
			Iterator_C iter = this.iterator();
			while(iter.hasNext())
				if (iter.next()==e) {
					iter.remove();
					size--;
					return;
				}
		}catch(Exception exc){
			System.out.println(exc);
		}
	}

	@Override
	public Iterator_C iterator(){//Returns The Iterator Of HashSet
		Iterator_C temp = new Iterator_C(this,hash);
		return temp;
	}

	/**Adds The Elements of Other Collection*/
	@Override
	public void addAll(Collection c){
		Iterator_C iter = c.iterator();
     	while(iter.hasNext())
      		this.add((E)iter.next());
	}
	
	/**Prints All Elements*/
	public void printAllElements(){
		Iterator_C iter = this.iterator();
		while (iter.hasNext())
			System.out.print((E)iter.next()+" ");
		System.out.println();
	}

	@Override
	public boolean containsAll(Collection c){/*Checks The Existence of Collection*/
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

	/**Removes All Elements of Collection Except Common Ones*/
	@Override
	public void retainAll(Collection c){
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
}