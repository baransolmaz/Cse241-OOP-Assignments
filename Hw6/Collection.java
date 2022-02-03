import java.util.*;
public interface Collection<E> {
	/**Adds An Element*/
	public void add(E e);
	/**Checks For An Element, If The Element Exists, Returns True*/
	public boolean contains(E e);
	/**Clears All Elements*/
	public void clear();
	/**Returns The Size*/
	public int size();
	/**Returns True If The Collection Is Empty*/
	public boolean isEmpty();
	/**Removes An Element*/
	public void remove(E e);
	/**Adds The Elements Of Collection*/
	public void addAll(Collection c);
	/**Checks For All Elements Of Collection, If All Elements Exist, Returns True*/
	public boolean containsAll(Collection c);
	/**Removes All Common Elements of Collection*/
	public void removeAll(Collection c);
	/**Removes All Elements of Collection Except Common Ones*/
	public void retainAll(Collection c);
	/**Returns The Iterator of Collection*/
	public Iterator_C iterator();
}