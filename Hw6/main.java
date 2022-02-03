import java.util.*;
class main {
	public static void main(String[] args) {
		
		System.out.println("\n---HashSet<Integer>---");
		HashSet<Integer> hash_i1 = new HashSet<Integer>();
		HashSet<Integer> hash_i2 = new HashSet<Integer>();

		System.out.println("\n .isEmpty() : "+hash_i1.isEmpty());
		for (int i=1;i<4 ;i++ ) {
			System.out.println(" .add("+i+") Used ");
			hash_i1.add(i);
		}
		System.out.println(" .isEmpty() : "+hash_i1.isEmpty());
		System.out.print("Current Elements: ");hash_i1.printAllElements();
		System.out.println("Current size(): "+hash_i1.size());

		hash_i1.remove(2);
		System.out.println("\n .remove(2) Used ");
		System.out.print("Current Elements: ");hash_i1.printAllElements();
		System.out.println("Current Size: "+hash_i1.size());
		System.out.println(" .contains(2) : "+hash_i1.contains(2));

		hash_i1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");hash_i1.printAllElements();
		System.out.println("Current Size: "+hash_i1.size());

		for (int i=1;i<4 ;i++ ) {
			hash_i1.add(i);
			hash_i2.add(i+2);
		}
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("hash_i1 Current Elements: ");hash_i1.printAllElements();
		System.out.println("hash_i1 Current Size: "+hash_i1.size());
		System.out.print("hash_i2 Current Elements: ");hash_i2.printAllElements();
		System.out.println("hash_i2 Current Size: "+hash_i2.size());
		
		System.out.println("\n .containsAll(hash_i2) : "+hash_i1.containsAll(hash_i2));
		hash_i1.addAll(hash_i2);
		System.out.println(" .addAll(hash_i2) Used ");
		System.out.println(" .containsAll(hash_i2) : "+hash_i1.containsAll(hash_i2));
		System.out.print("hash_i1 Current Elements: ");hash_i1.printAllElements();
		System.out.println("hash_i1 Current Size: "+hash_i1.size());

		hash_i1.removeAll(hash_i2);
		System.out.println("\n .removeAll(hash_i2) Used ");
		System.out.print("hash_i1 Current Elements: ");hash_i1.printAllElements();
		System.out.println("hash_i1 Current Size: "+hash_i1.size());System.out.println("\n .add(4) Used ");hash_i1.add(4);

		System.out.print("hash_i1 Current Elements: ");hash_i1.printAllElements();
		System.out.print("hash_i2 Current Elements: ");hash_i2.printAllElements();
		hash_i1.retainAll(hash_i2);
		System.out.println(" .retainAll(hash_i2) Used ");
		System.out.print("hash_i1 Current Elements: ");hash_i1.printAllElements();
		System.out.println("hash_i1 Current Size: "+hash_i1.size());

////////////////////

		System.out.println("\n\n\n---HashSet<String>---");
		HashSet<String> hash_s1 = new HashSet<String>();
		HashSet<String> hash_s2 = new HashSet<String>();

		System.out.println("\n .isEmpty() : "+hash_s1.isEmpty());
		
		System.out.println(" .add(\"A\") Used ");System.out.println(" .add(\"B\") Used ");System.out.println(" .add(\"C\") Used ");
		hash_s1.add("A");
		hash_s1.add("B");
		hash_s1.add("C");
		
		System.out.println(" .isEmpty() : "+hash_s1.isEmpty());
		System.out.print("Current Elements: ");hash_s1.printAllElements();
		System.out.println("Current size(): "+hash_s1.size());

		hash_s1.remove("B");
		System.out.println("\n .remove(\"B\") Used ");
		System.out.print("Current Elements: ");hash_s1.printAllElements();
		System.out.println("Current Size: "+hash_s1.size());
		System.out.println(" .contains(\"B\") : "+hash_s1.contains("B"));

		hash_s1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");hash_s1.printAllElements();
		System.out.println("Current Size: "+hash_s1.size());

		hash_s1.add("A");hash_s1.add("B");hash_s1.add("C");
		hash_s2.add("C");hash_s2.add("D");hash_s2.add("E");
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("hash_s1 Current Elements: ");hash_s1.printAllElements();
		System.out.println("hash_s1 Current Size: "+hash_s1.size());
		System.out.print("hash_s2 Current Elements: ");hash_s2.printAllElements();
		System.out.println("hash_s2 Current Size: "+hash_s2.size());
		
		System.out.println("\n .containsAll(hash_s2) : "+hash_s1.containsAll(hash_s2));
		hash_s1.addAll(hash_s2);
		System.out.println(" .addAll(hash_s2) Used ");
		System.out.println(" .containsAll(hash_s2) : "+hash_s1.containsAll(hash_s2));
		System.out.print("hash_s1 Current Elements: ");hash_s1.printAllElements();
		System.out.println("hash_s1 Current Size: "+hash_s1.size());

		hash_s1.removeAll(hash_s2);
		System.out.println("\n .removeAll(hash_s2) Used ");
		System.out.print("hash_s1 Current Elements: ");hash_s1.printAllElements();
		System.out.println("hash_s1 Current Size: "+hash_s1.size());System.out.println("\n .add(\"D\") Used ");hash_s1.add("D");

		System.out.print("hash_s1 Current Elements: ");hash_s1.printAllElements();
		System.out.print("hash_s2 Current Elements: ");hash_s2.printAllElements();
		hash_s1.retainAll(hash_s2);
		System.out.println(" .retainAll(hash_s2) Used ");
		System.out.print("hash_s1 Current Elements: ");hash_s1.printAllElements();
		System.out.println("hash_s1 Current Size: "+hash_s1.size());

////////////////////

		System.out.println("\n\n\n---ArrayList<Integer>---");
		ArrayList<Integer> array_i1 = new ArrayList<Integer>();
		ArrayList<Integer> array_i2 = new ArrayList<Integer>();

		System.out.println("\n .isEmpty() : "+array_i1.isEmpty());
		for (int i=1;i<4 ;i++ ) {
			System.out.println(" .add("+i+") Used ");
			array_i1.add(i);
		}
		System.out.println(" .isEmpty() : "+array_i1.isEmpty());
		System.out.print("Current Elements: ");array_i1.printAllElements();
		System.out.println("Current size(): "+array_i1.size());

		array_i1.remove(2);
		System.out.println("\n .remove(2) Used ");
		System.out.print("Current Elements: ");array_i1.printAllElements();
		System.out.println("Current Size: "+array_i1.size());
		System.out.println(" .contains(2) : "+array_i1.contains(2));

		array_i1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");array_i1.printAllElements();
		System.out.println("Current Size: "+array_i1.size());

		for (int i=1;i<4 ;i++ ) {
			array_i1.add(i);
			array_i2.add(i+2);
		}
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("array_i1 Current Elements: ");array_i1.printAllElements();
		System.out.println("array_i1 Current Size: "+array_i1.size());
		System.out.print("array_i2 Current Elements: ");array_i2.printAllElements();
		System.out.println("array_i2 Current Size: "+array_i2.size());
		
		System.out.println("\n .containsAll(array_i2) : "+array_i1.containsAll(array_i2));
		array_i1.addAll(array_i2);
		System.out.println(" .addAll(array_i2) Used ");
		System.out.println(" .containsAll(array_i2) : "+array_i1.containsAll(array_i2));
		System.out.print("array_i1 Current Elements: ");array_i1.printAllElements();
		System.out.println("array_i1 Current Size: "+array_i1.size());

		array_i1.removeAll(array_i2);
		System.out.println("\n .removeAll(array_i2) Used ");
		System.out.print("array_i1 Current Elements: ");array_i1.printAllElements();
		System.out.println("array_i1 Current Size: "+array_i1.size());System.out.println("\n .add(4) Used ");array_i1.add(4);

		System.out.print("array_i1 Current Elements: ");array_i1.printAllElements();
		System.out.print("array_i2 Current Elements: ");array_i2.printAllElements();
		array_i1.retainAll(array_i2);
		System.out.println(" .retainAll(array_i2) Used ");
		System.out.print("array_i1 Current Elements: ");array_i1.printAllElements();
		System.out.println("array_i1 Current Size: "+array_i1.size());

////////////////////

		System.out.println("\n\n\n---ArrayList<String>---");
		ArrayList<String> array_s1 = new ArrayList<String>();
		ArrayList<String> array_s2 = new ArrayList<String>();

		System.out.println("\n .isEmpty() : "+array_s1.isEmpty());
		
		System.out.println(" .add(\"A\") Used ");System.out.println(" .add(\"B\") Used ");System.out.println(" .add(\"C\") Used ");
		array_s1.add("A");
		array_s1.add("B");
		array_s1.add("C");
		
		System.out.println(" .isEmpty() : "+array_s1.isEmpty());
		System.out.print("Current Elements: ");array_s1.printAllElements();
		System.out.println("Current size(): "+array_s1.size());

		array_s1.remove("B");
		System.out.println("\n .remove(\"B\") Used ");
		System.out.print("Current Elements: ");array_s1.printAllElements();
		System.out.println("Current Size: "+array_s1.size());
		System.out.println(" .contains(\"B\") : "+array_s1.contains("B"));

		array_s1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");array_s1.printAllElements();
		System.out.println("Current Size: "+array_s1.size());

		array_s1.add("A");array_s1.add("B");array_s1.add("C");
		array_s2.add("C");array_s2.add("D");array_s2.add("E");
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("array_s1 Current Elements: ");array_s1.printAllElements();
		System.out.println("array_s1 Current Size: "+array_s1.size());
		System.out.print("array_s2 Current Elements: ");array_s2.printAllElements();
		System.out.println("array_s2 Current Size: "+array_s2.size());
		
		System.out.println("\n .containsAll(array_s2) : "+array_s1.containsAll(array_s2));
		array_s1.addAll(array_s2);
		System.out.println(" .addAll(array_s2) Used ");
		System.out.println(" .containsAll(array_s2) : "+array_s1.containsAll(array_s2));
		System.out.print("array_s1 Current Elements: ");array_s1.printAllElements();
		System.out.println("array_s1 Current Size: "+array_s1.size());

		array_s1.removeAll(array_s2);
		System.out.println("\n .removeAll(array_s2) Used ");
		System.out.print("array_s1 Current Elements: ");array_s1.printAllElements();
		System.out.println("array_s1 Current Size: "+array_s1.size());System.out.println("\n .add(\"D\") Used ");array_s1.add("D");

		System.out.print("array_s1 Current Elements: ");array_s1.printAllElements();
		System.out.print("array_s2 Current Elements: ");array_s2.printAllElements();
		array_s1.retainAll(array_s2);
		System.out.println(" .retainAll(array_s2) Used ");
		System.out.print("array_s1 Current Elements: ");array_s1.printAllElements();
		System.out.println("array_s1 Current Size: "+array_s1.size());

////////////////////
		
		System.out.println("\n\n\n---LinkedList<Integer>---");

		LinkedList<Integer> link_i1 = new LinkedList<Integer>();
		LinkedList<Integer> link_i2 = new LinkedList<Integer>();

		System.out.println("\n .isEmpty() : "+link_i1.isEmpty());
		for (int i=1;i<4 ;i++ ) {
			System.out.println(" .add("+i+") Used ");
			link_i1.add(i);
		}
		System.out.println(" .isEmpty() : "+link_i1.isEmpty());
		System.out.print("Current Elements: ");link_i1.printAllElements();
		System.out.println("Current size(): "+link_i1.size());

		link_i1.remove(2);
		System.out.println("\n .remove(2) Used ");
		System.out.print("Current Elements: ");link_i1.printAllElements();
		System.out.println("Current Size: "+link_i1.size());
		System.out.println(" .contains(2) : "+link_i1.contains(2));

		link_i1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");link_i1.printAllElements();
		System.out.println("Current Size: "+link_i1.size());

		for (int i=1;i<4 ;i++ ) {
			link_i1.add(i);
			link_i2.add(i+2);
		}
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());
		System.out.print("link_i2 Current Elements: ");link_i2.printAllElements();
		System.out.println("link_i2 Current Size: "+link_i2.size());
		
		System.out.println("\n .containsAll(link_i2) : "+link_i1.containsAll(link_i2));
		link_i1.addAll(link_i2);
		System.out.println(" .addAll(link_i2) Used ");
		System.out.println(" .containsAll(link_i2) : "+link_i1.containsAll(link_i2));
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());

		link_i1.removeAll(link_i2);
		System.out.println("\n .removeAll(link_i2) Used ");
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());System.out.println("\n .add(4) Used ");link_i1.add(4);

		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.print("link_i2 Current Elements: ");link_i2.printAllElements();
		link_i1.retainAll(link_i2);
		System.out.println(" .retainAll(link_i2) Used ");
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());	
		
		try{
			System.out.print("\n .element() Used --");System.out.println( link_i1.element());
		}catch(Exception exc){
			System.out.println(exc);
		}
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());
		try{
			System.out.print("\n.poll() Used --");System.out.println( link_i1.poll());
		}catch(Exception exc){
			System.out.println(exc);
		}
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());
		try{
			System.out.print(" .poll() Used --");System.out.println( link_i1.poll());
		}catch(Exception exc){
			System.out.println(exc);
			System.out.println("\n .offer(8) Used --");link_i1.offer(8);
		}
		System.out.print("link_i1 Current Elements: ");link_i1.printAllElements();
		System.out.println("link_i1 Current Size: "+link_i1.size());
		
////////////////////

		System.out.println("\n\n\n---LinkedList<String>---");

		LinkedList<String> link_s1 = new LinkedList<String>();
		LinkedList<String> link_s2 = new LinkedList<String>();

		System.out.println("\n .isEmpty() : "+link_s1.isEmpty());
		System.out.println(" .add(\"A\") Used ");System.out.println(" .add(\"B\") Used ");System.out.println(" .add(\"C\") Used ");
		link_s1.add("A");
		link_s1.add("B");
		link_s1.add("C");
		System.out.println(" .isEmpty() : "+link_s1.isEmpty());
		System.out.print("Current Elements: ");link_s1.printAllElements();
		System.out.println("Current size(): "+link_s1.size());

		link_s1.remove("B");
		System.out.println("\n .remove(\"B\") Used ");
		System.out.print("Current Elements: ");link_s1.printAllElements();
		System.out.println("Current Size: "+link_s1.size());
		System.out.println(" .contains(\"B\") : "+link_s1.contains("B"));

		link_s1.clear();
		System.out.println("\n .clear() Used ");
		System.out.print("Current Elements: ");link_s1.printAllElements();
		System.out.println("Current Size: "+link_s1.size());

		link_s1.add("A");link_s1.add("B");link_s1.add("C");
		link_s2.add("C");link_s2.add("D");link_s2.add("E");
		
		System.out.println("\n--Some add( ) Methods Used-- ");
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());
		System.out.print("link_s2 Current Elements: ");link_s2.printAllElements();
		System.out.println("link_s2 Current Size: "+link_s2.size());
		
		System.out.println("\n .containsAll(link_s2) : "+link_s1.containsAll(link_s2));
		link_s1.addAll(link_s2);
		System.out.println(" .addAll(link_s2) Used ");
		System.out.println(" .containsAll(link_s2) : "+link_s1.containsAll(link_s2));
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());

		link_s1.removeAll(link_s2);
		System.out.println("\n .removeAll(link_s2) Used ");
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());System.out.println("\n .add(\"D\") Used ");link_s1.add("D");

		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.print("link_s2 Current Elements: ");link_s2.printAllElements();
		link_s1.retainAll(link_s2);
		System.out.println(" .retainAll(link_s2) Used ");
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());	
		
		try{
			System.out.print("\n .element() Used --");System.out.println( link_s1.element());
		}catch(Exception exc){
			System.out.println(exc);
		}
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());
		try{
			System.out.print("\n.poll() Used --");System.out.println( link_s1.poll());
		}catch(Exception exc){
			System.out.println(exc);
		}
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());
		try{
			System.out.print(" .poll() Used --");System.out.println( link_s1.poll());
		}catch(Exception exc){
			System.out.println(exc);
			System.out.println("\n .offer(\"Z\") Used --");link_s1.offer("Z");
		}
		System.out.print("link_s1 Current Elements: ");link_s1.printAllElements();
		System.out.println("link_s1 Current Size: "+link_s1.size());
	}
}