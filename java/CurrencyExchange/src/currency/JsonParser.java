package currency;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import org.json.*;


public class JsonParser {
	private JSONObject json;
	
	public JsonParser(JSONObject object) {
		json = object;
	}
	
	public String getValue(String key) {
		return json.getString(key);
	}
	
	public HashMap<String, ArrayList<Double>> getRates() {
		JSONArray rates = json.getJSONArray("rates");
		ArrayList<String> currencies = new ArrayList<String>(
	            Arrays.asList("USD", "EUR", "GBP", "CHF", "AUD"));
		JSONArray filteredrates = new JSONArray();
		HashMap<String, ArrayList<Double>> ratesMap = new HashMap<String, ArrayList<Double>>();
		for (int i = 0; i < rates.length(); i++) {
			if (currencies.contains(rates.getJSONObject(i).getString("code"))) {
				filteredrates.put(rates.getJSONObject(i));
			}
		}
		for (int i = 0; i < filteredrates.length(); i++) {
			ArrayList<Double> tmp = new ArrayList<Double>();
			tmp.add(filteredrates.getJSONObject(i).getDouble("bid")); // purchase
			tmp.add(filteredrates.getJSONObject(i).getDouble("ask")); // sale
			ratesMap.put(filteredrates.getJSONObject(i).getString("code"), tmp);
		}
		return ratesMap;
	}
}
