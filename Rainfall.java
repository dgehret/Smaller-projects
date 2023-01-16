import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Collections;


public class Rainfall {

	private static void die() {
		System.out.println("BAD INPUT!");
		System.exit(0);
	}

	private static void InputData(ArrayList<Integer> data) {
		int measurement = 0;
		while (true) {
			try {
				measurement = Integer.parseInt(input.nextLine());
				if (measurement == -1) break;
				if (measurement >= 0) data.add(measurement);
			} 
			catch (NumberFormatException e) {
				die();
			}
		}
	}

	private static void AvgDaily(ArrayList<Integer> data) {
		if (data.size() == 0) {
			System.out.println("NO DATA");
			return;
		}
		int sum = 0;
		for (Integer elem : data)
			sum += elem;
		int avg = sum / data.size();
		System.out.println(avg);
	}

	private static void AvgRainy(ArrayList<Integer> data) {
		int sum = 0, counter = 0;
		for (Integer elem : data)
			if (elem > 0) {
				sum += elem;
				counter++;
			}
		if (counter == 0) {
			System.out.println("NO DATA");
			return;
		}
		int avg = sum / counter;
		System.out.println(avg);
	}

	private static void DaysWithRain(ArrayList<Integer> data) {
		if (data.size() == 0) {
			System.out.println("NO DATA");
			return;
		}
		int counter = 0;
		for (Integer elem : data) {
			if (elem > 0)
				counter++;
		}
		System.out.println(counter);
	}

    public static void MaxRain(ArrayList<Integer> list) {
        // check list is empty or not
        if (list == null || list.size() == 0) {
            System.out.println("NO DATA");
        }

        // create a new list to avoid modification
        // in the original list
        List<Integer> sortedlist = new ArrayList<>(list);

        // sort list in natural order
        Collections.sort(sortedlist);

        // last element in the sorted list would be maximum
		if (sortedlist.indexOf(0) == 0) System.out.println("NO DATA");
		else System.out.println(sortedlist.get(sortedlist.size() - 1));
    }

	private static void TopFive(ArrayList<Integer> data) {
		List<Integer> sortedlist = new ArrayList<>(data);
		Collections.sort(sortedlist);
		Collections.reverse(sortedlist);
		if (sortedlist.indexOf(0) == 0) {
			System.out.println("NO DATA");
			return;
		}
		while (sortedlist.size() > 5)
			sortedlist.remove(sortedlist.size() - 1);
		for (Integer elem : sortedlist)
			System.out.println(elem);
	}

	public static void main(String[] args) {
		java.util.Scanner input = new java.util.Scanner(System.in); 

		ArrayList<Integer> data = new ArrayList<>();
		System.out.println("Welcome to Java Rainfall!\nPlease enter daily rainfall data (-1 to quit):");
		InputData(data);
		while (true) {
			System.out.println("1) Average daily rainfall");
			System.out.println("2) Average rainfall on rainy days");
			System.out.println("3) Count of days that had rain");
			System.out.println("4) Maximum rainfall");
			System.out.println("5) Top 5 days of rain");
			System.out.println("6) Quit");
			int choice = input.nextInt();
			if (choice < 1 || choice > 6) die();	//Bounds checking for MENU
			if (choice == 1) AvgDaily(data);
			if (choice == 2) AvgRainy(data);
			if (choice == 3) DaysWithRain(data);
			if (choice == 4) MaxRain(data);
			if (choice == 5) TopFive(data);
			if (choice == 6) System.exit(0);
		}
	}
}
