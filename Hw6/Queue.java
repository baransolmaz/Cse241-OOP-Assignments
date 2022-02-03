public interface Queue<E> extends Collection<E> {
	/** Adds An Element*/
	public void add(E e);
	/**Returns The Head Of Queue or Throws Exception, If There Is No Element */
	public E element()throws Exception;
	/** Adds An Element*/
	public void offer(E e); 
	/**Returns And Removes The Head Of Queue or Throws Exception, If There Is No Element*/
	public E poll()throws Exception;
}