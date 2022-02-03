import java.util.*;
public class Iterator_C<E> implements Iterator<E> {
	private E itr[];
	private int size,location;
	private Class[] type;
	/**Constructor*/
	public Iterator_C(Collection c,E[] arr){
		size=c.size();
		itr= arr;
		location=-1;
		type=c.getClass().getInterfaces();
	}
	/**Returns True, If There Is More Element */
	@Override
	public boolean hasNext(){
		if (size-1>location) {
			return true;
		}else
			return false;
	}
	/**Returns Next Element and Increases Index*/
	@Override
	public E next()throws NoSuchElementException{
		if (hasNext()) {
			location++;
			return itr[location];
		}else
			throw new NoSuchElementException();
	}
	/**Removes An Element, Throws Exception If The Object Is Queue*/
	@Override
	public void remove() throws Exception{
		for(int i= 0 ;i<type.length;i++)
			if (type[i].getName() == "Queue") 
					throw new Exception("Unsupported Type ---Queue---");
		for(int i= location ;i<size-1;i++){
			itr[i]=itr[i+1];
		}
		itr[size-1]=null;
		size--;
	}
}