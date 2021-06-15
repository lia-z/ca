package test;

import java.util.StringTokenizer;

public class 과제posfix {

	public static void main(String[] args) {
		String s1 = new String("2.0*3.0-((4.0+5.0)*2.0)-4.0+5.0*2.0=");
		String[] s2;
		s2 = postfix(s1); // 식을 postfix함
		for (int i = 0; i < s2.length; i++) { // 출력
			System.out.print(s2[i] + " ");
		}
		System.out.print("\n계산 = " + evalution(s2));
	}

	public static int weight(String a) {
		int x = 0;
		if (a.equals("*") || a.equals("/"))
			x = 3;
		else if (a.equals("+") || a.equals("-"))
			x = 2;
		return x;
	}

	public static String[] postfix(String s1) {
		StringTokenizer st1 = new StringTokenizer(s1, "*-=+()/", true);
		StringTokenizer st2 = new StringTokenizer(s1, "*-=+()/", true);
		GStack<String> ss = new GStack<String>();
		String s2 = new String();
		int n = 0;
		
		while (st1.hasMoreTokens()) {
			s1 = st1.nextToken();
			if(s1.equals("(") || s1.equals(")") || s1.equals("="))
				continue;
			else
				n++;
		}
		
		String[] zz = new String[n];
		n=0;
		
		while (st2.hasMoreTokens()) {
			s1 = st2.nextToken();
			try {   //숫자면 배열에 바로넣는다
				Double.parseDouble(s1);
				zz[n++] = s1;
			} catch (NumberFormatException e) {
				//아무것도 없거나 (는 바로 push
				if (ss.tos == 0 || s1.equals("("))
					ss.push(s1);
				//)는 (가있을때까지 pop
				else if(s1.equals(")")) {
					while(true) {
						if(ss.val().equals("(")) {
							ss.pop();
							break;
						}
						zz[n++] = ss.pop();
					}
				}
				else if(s1.equals("=")) {
					while(ss.tos != 0) {
						zz[n++] = ss.pop();
					}
					break;
				}
				else if(weight(ss.val()) >= weight(s1) ) {
					zz[n++] = ss.pop();
					ss.push(s1);
				}
				else if(weight(ss.val()) < weight(s1) ) {
					ss.push(s1);
				}
				continue;
			}
		}
		return zz;
	}

	public static double evalution(String[] s) {
		GStack<Double> ds = new GStack<Double>();
		double a,b;
		for(int i = 0 ; i<s.length ; i++) {
			try {   //숫자면 puch
				ds.push(Double.parseDouble(s[i]));
			} catch (NumberFormatException e) {
				//둘다 pop해서  계산하고 push
				b = ds.pop();
				a = ds.pop();
				ds.push(calculation(a,b,s[i]));
				continue;
			}
		}
		return ds.pop();
	}
	public static double calculation (double a , double b , String s) {
		if(s.equals("+"))
			return a+b;
		else if(s.equals("-"))
			return a-b;
		else if(s.equals("*"))
			return a*b;
		else
			return a/b;
	}
	
}

class GStack<T> {
	int tos, a;
	Object[] stck;

	public GStack() {
		tos = 0;
		stck = new Object[10];
	}

	public void push(T item) {
		if (tos == 10)
			return;
		stck[tos] = item;
		tos++;
	}

	public T pop() {
		if (tos == 0)
			return null;
		tos--;
		return (T) stck[tos];
	}

	public T val() {
		return (T) stck[tos - 1];
	}
}