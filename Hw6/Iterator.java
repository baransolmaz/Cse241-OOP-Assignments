import java.util.*;
public interface Iterator<E> {
	/**Returns True, If There Is More Element */
	public boolean hasNext();
	/**Returns Next Element and Increases Index*/
	public E next() throws NoSuchElementException;
	/**Removes An Element, Throws Exception If The Object Is Queue*/
	public void remove()throws Exception;
}