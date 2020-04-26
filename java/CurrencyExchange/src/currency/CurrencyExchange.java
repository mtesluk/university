package currency;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import java.awt.FlowLayout;
import javax.swing.JButton;
import java.awt.CardLayout;
import java.awt.Color;
import net.miginfocom.swing.MigLayout;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.awt.event.ActionEvent;
import javax.swing.UIManager;
import javax.swing.JComboBox;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JTextPane;
import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;

import org.json.*;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.AutoBinding;
import org.jdesktop.beansbinding.Bindings;
import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.Converter;
import org.jdesktop.beansbinding.ObjectProperty;
import org.jdesktop.beansbinding.Property;

public class CurrencyExchange extends JFrame {

	private String url = "http://api.nbp.pl/api/exchangerates/tables/c/?format=json";
	private JPanel contentPane;
	private JTextField txtConvertFrom;
	private JTextField txtConvertTo;
	private JTextField txtPLN;
	private JTextField txtLoadData_viewer;
	private JTextPane value_PLN;
	private JTextPane value_Converted;
	private JComboBox selectCurrency;
	private String[] currencies = { "USD", "EUR", "GBP", "CHF", "AUD" };
	HashMap<String, ArrayList<Double>> ratesMap;
	private JTextPane purchaseUSD;
	private JTextPane txtDirty;
	private JTextField txtFilteredValuedigits;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					CurrencyExchange frame = new CurrencyExchange();
					frame.setVisible(true);
					frame.setTitle("CurrencyExchange");
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public CurrencyExchange() {
		DatabaseHandler db = new DatabaseHandler();
		db.connect();
		db.createNewTableIfNotExist("currency");
		ArrayList<String> dates = db.selectAll("currency", "date");
		System.out.println("INFO: Dates in DB: " + dates);
		db.disconnect();
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JPanel menu = new JPanel();
		menu.setBackground(Color.DARK_GRAY);
		contentPane.add(menu, BorderLayout.NORTH);
		menu.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 5));

		JPanel dashboard = new JPanel();
		contentPane.add(dashboard, BorderLayout.CENTER);
		dashboard.setLayout(new CardLayout(0, 0));
		
		JPanel appViewer = new JPanel();
		appViewer.setBackground(Color.GRAY);
		dashboard.add(appViewer, "name_714913922581402");
		appViewer.setLayout(new MigLayout("", "[125px,grow][125px,grow][125px,grow]", "[grow][grow][grow][grow][grow][grow][][]"));

		JPanel appConverter = new JPanel();
		appConverter.setBackground(Color.LIGHT_GRAY);
		dashboard.add(appConverter, "name_714925199361600");
		appConverter.setLayout(new MigLayout("", "[125px,grow][125px,grow][125px,grow]", "[grow][grow][grow][grow][]"));

		value_Converted = new JTextPane();
		value_Converted.getDocument().addDocumentListener(onChangeConverter());
		
		txtFilteredValuedigits = new JTextField();
		txtFilteredValuedigits.setEditable(false);
		txtFilteredValuedigits.setText("Filtered value (digits):");
		appConverter.add(txtFilteredValuedigits, "cell 2 0,growx,aligny bottom");
		txtFilteredValuedigits.setColumns(10);
		appConverter.add(value_Converted, "cell 2 1,growx,aligny top");
		
		value_PLN = new JTextPane();
		appConverter.add(value_PLN, "cell 2 2,growx,aligny bottom");
		
		txtConvertFrom = new JTextField();
		txtConvertFrom.setEditable(false);
		txtConvertFrom.setText("Convert:");
		appConverter.add(txtConvertFrom, "cell 0 1,growx,aligny top");
		txtConvertFrom.setColumns(10);
		
		selectCurrency = new JComboBox(currencies);
		appConverter.add(selectCurrency, "flowy,cell 1 1,growx,aligny top");
		
		txtConvertTo = new JTextField();
		txtConvertTo.setEditable(false);
		txtConvertTo.setText("Convert:");
		appConverter.add(txtConvertTo, "cell 0 2,growx,aligny bottom");
		txtConvertTo.setColumns(10);
		
		txtPLN = new JTextField();
		txtPLN.setFont(new Font("Tahoma", Font.PLAIN, 12));
		txtPLN.setEditable(false);
		txtPLN.setHorizontalAlignment(SwingConstants.LEFT);
		txtPLN.setText("PLN");
		appConverter.add(txtPLN, "cell 1 2,growx,aligny bottom");
		txtPLN.setColumns(10);
		
		JLabel lblCurrency = new JLabel("CURRENCY");
		lblCurrency.setForeground(Color.WHITE);
		lblCurrency.setFont(new Font("Tahoma", Font.BOLD, 12));
		appViewer.add(lblCurrency, "cell 0 0,alignx center");
		
		JLabel lblPurchase = new JLabel("PURCHASE");
		lblPurchase.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblPurchase.setForeground(Color.WHITE);
		appViewer.add(lblPurchase, "cell 1 0,alignx center");
		
		JLabel lblSale = new JLabel("SALE");
		lblSale.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblSale.setForeground(Color.WHITE);
		appViewer.add(lblSale, "cell 2 0,alignx center");
		
		JLabel lblUsd = new JLabel("USD");
		lblUsd.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblUsd.setForeground(UIManager.getColor("CheckBox.highlight"));
		appViewer.add(lblUsd, "cell 0 1,alignx center");
		
		purchaseUSD = new JTextPane();
		purchaseUSD.setEditable(false);
		appViewer.add(purchaseUSD, "cell 1 1,grow");
		
		JTextPane saleUSD = new JTextPane();
		saleUSD.setEditable(false);
		appViewer.add(saleUSD, "cell 2 1,grow");
		
		JLabel lblEur = new JLabel("EUR");
		lblEur.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblEur.setForeground(UIManager.getColor("Button.disabledShadow"));
		appViewer.add(lblEur, "cell 0 2,alignx center");
		
		JTextPane purchaseEUR = new JTextPane();
		purchaseEUR.setEditable(false);
		appViewer.add(purchaseEUR, "cell 1 2,grow");
		
		JTextPane saleEUR = new JTextPane();
		saleEUR.setEditable(false);
		appViewer.add(saleEUR, "cell 2 2,grow");
		
		JLabel lblGbp = new JLabel("GBP");
		lblGbp.setForeground(UIManager.getColor("Button.disabledShadow"));
		lblGbp.setFont(new Font("Tahoma", Font.BOLD, 12));
		appViewer.add(lblGbp, "cell 0 3,alignx center");
		
		JTextPane purchaseGBP = new JTextPane();
		purchaseGBP.setEditable(false);
		appViewer.add(purchaseGBP, "cell 1 3,grow");
		
		JTextPane saleGBP = new JTextPane();
		saleGBP.setEditable(false);
		appViewer.add(saleGBP, "cell 2 3,grow");
		
		JLabel lblChf = new JLabel("CHF");
		lblChf.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblChf.setForeground(UIManager.getColor("Button.disabledShadow"));
		appViewer.add(lblChf, "cell 0 4,alignx center");
		
		JTextPane purchaseCHF = new JTextPane();
		purchaseCHF.setEditable(false);
		appViewer.add(purchaseCHF, "cell 1 4,grow");
		
		JTextPane saleCHF = new JTextPane();
		saleCHF.setEditable(false);
		appViewer.add(saleCHF, "cell 2 4,grow");
		
		JLabel lblAud = new JLabel("AUD\r\n");
		lblAud.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblAud.setForeground(UIManager.getColor("Button.disabledShadow"));
		appViewer.add(lblAud, "cell 0 5,alignx center");
		
		JTextPane purchaseAUD = new JTextPane();
		purchaseAUD.setEditable(false);
		appViewer.add(purchaseAUD, "cell 1 5,grow");
		
		JTextPane saleAUD = new JTextPane();
		saleAUD.setEditable(false);
		appViewer.add(saleAUD, "cell 2 5,grow");
		
		txtLoadData_viewer = new JTextField();
		txtLoadData_viewer.setEditable(false);
		txtLoadData_viewer.setText("Load from DB...");
		appViewer.add(txtLoadData_viewer, "cell 1 6,growx");
		txtLoadData_viewer.setColumns(10);
		
		JComboBox selectToLoad_viewer = new JComboBox(dates.toArray());
		selectToLoad_viewer.setSelectedIndex(-1);
		selectToLoad_viewer.setToolTipText("Load from DB...");
		appViewer.add(selectToLoad_viewer, "cell 1 7,growx");
		selectToLoad_viewer.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(selectToLoad_viewer.isShowing()) {
					db.connect();
					ratesMap = db.selectRow("currency", "date", selectToLoad_viewer.getSelectedItem().toString());
					System.out.println("INFO: Selected data from: " + selectToLoad_viewer.getSelectedItem().toString());
					System.out.println("INFO: Rates status: " + ratesMap);
					purchaseUSD.setText(ratesMap.get("USD").get(0).toString());
					saleUSD.setText(ratesMap.get("USD").get(1).toString());
					purchaseEUR.setText(ratesMap.get("EUR").get(0).toString());
					saleEUR.setText(ratesMap.get("EUR").get(1).toString());
					purchaseGBP.setText(ratesMap.get("GBP").get(0).toString());
					saleGBP.setText(ratesMap.get("GBP").get(1).toString());
					purchaseCHF.setText(ratesMap.get("CHF").get(0).toString());
					saleCHF.setText(ratesMap.get("CHF").get(1).toString());
					purchaseAUD.setText(ratesMap.get("AUD").get(0).toString());
					saleAUD.setText(ratesMap.get("AUD").get(1).toString());
					db.disconnect();
				}
			}
		});
		
		JComboBox selectToDelete_viewer = new JComboBox(dates.toArray());
		selectToDelete_viewer.setSelectedIndex(-1);
		selectToDelete_viewer.setToolTipText("Delete from DB...");
		appViewer.add(selectToDelete_viewer, "cell 2 7,growx");
		selectToDelete_viewer.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		
		JButton btnDeleteRowIn = new JButton("Delete from DB...");
		btnDeleteRowIn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				db.connect();
				db.delete("currency", selectToDelete_viewer.getSelectedItem().toString());
				System.out.println("INFO: Removed data from: " + selectToDelete_viewer.getSelectedItem().toString());
				selectToDelete_viewer.removeItemAt(selectToDelete_viewer.getSelectedIndex());
				selectToDelete_viewer.setSelectedIndex(-1);
				db.disconnect();
			}
		});
		appViewer.add(btnDeleteRowIn, "cell 2 6");
		
		JButton btnLoadDataApi = new JButton("Load data from API");
		appViewer.add(btnLoadDataApi, "cell 0 7,alignx center");
		btnLoadDataApi.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				HttpHandler handler = new HttpHandler(url);
				try {
					handler.load();
				} catch (IOException err) {
					err.printStackTrace();
				}
				JSONObject data = handler.getJsonObject();
				String json_data = data.toString();
				Boolean valid = handler.isJSONValid(json_data);
				if (valid == true) {
					System.out.println("INFO: Valid JSON!");
					JsonParser parser = new JsonParser(data);
					String date = parser.getValue("effectiveDate");
					ratesMap = parser.getRates();
					System.out.println("INFO: API request for: " + date);
					System.out.println("INFO: Rates status: " + ratesMap);
					
					db.connect();
					final boolean exist = db.ifExistsRow("currency", "date", date);
					if (exist == false) {
						db.insert("currency", date, ratesMap);
						selectToLoad_viewer.addItem(date);
						selectToDelete_viewer.addItem(date);
					}
					else {
						System.out.println("INFO: Entry for " + date + " already exists!");
					}
					db.disconnect();
				}
				else {
					System.out.println("ERROR: Invalid JSON!");
				}
				
			}
		});
		
		JButton btnViewer = new JButton("Check courses");
		btnViewer.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				dashboard.removeAll();
				dashboard.add(appViewer);
				dashboard.repaint();
				dashboard.revalidate();
			}
		});
		menu.add(btnViewer);
		
		JButton btnConverter = new JButton("Convert currencies");
		btnConverter.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				dashboard.removeAll();
				dashboard.add(appConverter);
				dashboard.repaint();
				dashboard.revalidate();
			}
		});
		menu.add(btnConverter);
	}
	
	private DocumentListener onChangeConverter() {
		return new DocumentListener() {
			@Override
			public void insertUpdate(DocumentEvent e) {
				initDataBindings();
			}

			@Override
			public void removeUpdate(DocumentEvent e) {
				initDataBindings();
			}

			@Override
			public void changedUpdate(DocumentEvent e) {
				initDataBindings();
			}
		};
	}
	
	protected void initDataBindings() {
		Property jTextPaneBeanProperty = BeanProperty.create("text");
		Property jTextPaneBeanProperty_1 = BeanProperty.create("text");
		AutoBinding autoBinding = Bindings.createAutoBinding(UpdateStrategy.READ_WRITE, value_Converted, jTextPaneBeanProperty, value_PLN, jTextPaneBeanProperty_1);
		BindConverter conv = new BindConverter(ratesMap.get(selectCurrency.getSelectedItem().toString()).get(0));
		autoBinding.setConverter(conv);
		autoBinding.bind();
	}
}