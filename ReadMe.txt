The regular trolleys which we use in supermarkets require to be pushed or pulled along with us. This can be inconvenient if the weight of products is more. Also, after buying, we need to wait for billing of all the commodities. One of the solutions of these problems would be “Customer Following Automated Shopping Trolley” which will follow its customer automatically, hence saving the customer from carrying their own load. It will also have its own integrated billing system which will add each of the commodities scanned and hence generate the 
shopping bill.

The project uses 3 boards:
1) Arduino Uno
-- For following logic
-- Refer Following.ino

2) Arduino Mega
-- For Billing Process
-- For Weight Checking Process
-- Refer barcode_weighing_ArduinoMega.ino

3) ESP8266 WiFi Module
-- For Product Database access
-- Refer barcode_weighing_compare.ino

For connection of ESP, Arduino and Product Database, php is used.
1) insert_1.php
-- This code is used to fill the product database
2) post-esp.php
-- This code receives product id from arduino and sends back the weight of that particular product for further processing
3) shop_list.php
-- This code updates the shopping list as per the items filled in the trolley




