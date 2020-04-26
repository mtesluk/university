package currency;

public class BindConverter extends org.jdesktop.beansbinding.Converter<String, String>{
	private Double rate;
	
	public BindConverter(Double data) {
		rate = data;
	}
	
	@Override
	public String convertForward(String arg0) {
		String text = arg0.replaceAll("\\D+","");
		Double result;
		if (text.length() == 0) {
			result = 0.0;
		} else {
			result = Double.parseDouble(text);
		}
		return String.valueOf(result*rate);
	}

	@Override
	public String convertReverse(String arg0) {
		System.out.println("aaaa");
		return arg0;
	}

}

