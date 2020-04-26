package currency;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.HashMap;

import org.json.JSONArray;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

class getRatesTest {

	@Test
	void test() {
		JSONObject data = new JSONObject();
		data.put("effectiveDate","2019-04-26)");
		JSONArray array = new JSONArray();
		JSONObject item1 = new JSONObject(); item1.put("code", "USD"); item1.put("bid", 3.8152); item1.put("ask", 6.8922); array.put(item1);
		JSONObject item2 = new JSONObject(); item2.put("code", "AUD"); item2.put("bid", 2.8152); item2.put("ask", 4.8922); array.put(item2);
		JSONObject item3 = new JSONObject(); item3.put("code", "EUR"); item3.put("bid", 5.8152); item3.put("ask", 3.8922); array.put(item3);
		JSONObject item4 = new JSONObject(); item4.put("code", "CHF"); item4.put("bid", 1.8152); item4.put("ask", 2.8922); array.put(item4);
		JSONObject item5 = new JSONObject(); item5.put("code", "GBP"); item5.put("bid", 2.8152); item5.put("ask", 1.8922); array.put(item5);
		data.put("rates", array);
		
		JsonParser parser = new JsonParser(data);
		HashMap<String, ArrayList<Double>> ratesMap = parser.getRates();
		
		assertEquals(ratesMap.get("USD").get(0), item1.get("bid"));
		assertEquals(ratesMap.get("AUD").get(1), item2.get("ask"));
		assertEquals(ratesMap.get("EUR").get(0), item3.get("bid"));
		assertEquals(ratesMap.get("CHF").get(1), item4.get("ask"));
		assertEquals(ratesMap.get("GBP").get(0), item5.get("bid"));		
	}

}
