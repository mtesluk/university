package currency;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

class HttpHandlerTest {

	@Test
	void test() {
		
		// API response:
	 	// [ { "id": 1, "userID": 1 } ]
		
		String url = "http://www.json-generator.com/api/json/get/ceJTWbblBu?indent=2";
		String response = "{\"id\":1,\"userID\":1}";
		HttpHandler handler = new HttpHandler(url);
		try {
			handler.load();
		} catch (IOException e) {
			e.printStackTrace();
		}
		String data = handler.getJsonObject().toString();
		System.out.println(data);
		
		assertEquals(response, data);	
		
	}

}
