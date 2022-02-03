import java.util.*;
@SuppressWarnings("unchecked")
public class ArrayList<E> implements List<E> {
	private E arraylist[];
	private int size;
	
	@Override
	public int size(){//Returns Size
		return size;
	} 
	/**Constructor*/
	public ArrayList(){
		size=0;
		arraylist= (E[]) new Object[1];
	} 

	@Override
	public void add(E e){//Adds an Element Into The Array
		E trash[];
		trash=(E[]) new Object[size+1];
		if (size>0) {
			for (int i=0;i<size() ;i++ )
				trash[i]=arraylist[i];
		}
		arraylist=(E[]) new Object[size+1];
		for (int i=0;i<size() ;i++ )
			arraylist[i]=trash[i];

		arraylist[size]=e;
		size++;
	}
	
	@Override
	public void clear(){//Clears All Elements
		size=0;
		arraylist= (E[]) new Object[1];
	}
	
	@Override
	public boolean isEmpty(){//Returns True If There Is No Element
		if (this.size()==0) {
			return true;
		}else
			return false;
	}
	
	@Override
	public boolean contains(E e){//Checks For an Element
		for (int i=0;i<this.size();i++ ) 
			if (arraylist[i]==(e))
				return true;
		return false;
	}
	
	@Override
	public void remove(E e){//Removes An Element 
		try{
			Iterator_C iter = this.iterator();
			while(iter.hasNext())
				if (iter.next()==e) {
					iter.remove();
					size--;
					//return;
				}
		}catch(Exception exc){
			System.out.println(exc);
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
		for(int i=0; i<this.size();i++)
			while(iter.hasNext()){
					this.remove((E)iter.next());
			}
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
	public Iterator_C iterator(){//Returns The Iterator Of ArrayList
		Iterator_C temp = new Iterator_C(this,arraylist);
		return temp;
	}

	/**Prints All Elements*/
	public void printAllElements(){ 
		Iterator_C iter = this.iterator();
		while (iter.hasNext())
			System.out.print((E)iter.next()+" ");
		
		System.out.println();
	}

	/**Returns X-th The Element Of List*/
	public E getElement(int x){//For Random Access
		try{
			if (checkIndex(x))
				return (E)arraylist[x];
		}catch(Exception ex){
			System.out.println(ex);
		}
		return null;
	}
	/**Changes X-th The Element Of List with E*/
	public void setElement(int x,E e){//For Random Access
		try{
			if (checkIndex(x))
				arraylist[x]=e;
		}catch(Exception exc){
			System.out.println(exc);
		}
	}
	/**Checks The Index; Returns True ,If The Index Is Valid; If Not Valid ,Throws Exception*/
	private boolean checkIndex(int x)throws IndexOutOfBoundsException{
		if (this.size()>x && x>=0)
			return true;
		else
			throw new IndexOutOfBoundsException("Invalid Index -Max: "+(size()-1));
	}
}