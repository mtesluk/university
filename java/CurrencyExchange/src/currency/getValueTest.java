package currency;

import static org.junit.jupiter.api.Assertions.*;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

class getValueTest {

	@Test
	void test() {
		JSONObject obj = new JSONObject();
		obj.put("date", "2019-04-26");
		obj.put("city", "Bielsko-Biala");
		
		JsonParser parser = new JsonParser(obj);
		
		String city = parser.getValue("city");
		String date = parser.getValue("date");
		
		assertEquals(obj.getString("city"), city);
		assertEquals(obj.getString("date"), date);		
	}

}
