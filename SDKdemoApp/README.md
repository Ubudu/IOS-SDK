UbuduSDKdemoApp
===============

A simple demo app to illustrate possible usage scenario of the SDK with i-beacons. To start using and testing the demo app you need to have different i-beacons configured.
All beacons have the same proximuty UID : 'F2A74FC4-7625-44DB-9B08-CB7E130B2029' and the same major 12300 and have been configured only with a single proximity range (in real life settings it might be more appropriate to combine several proximity ranges) on the 'on_entry' event. 
- **VIP welcome*** : the arrival of user with a given name is notified (through a push notification) to the sales rep (require to have Ubudu Merchant app - contact us if required and cannot be tested otherwise - contact us). (Minor : 1310 - proximity : far)
- **Click and collect*** : the user is notified when he arrives (detect a beacon at far distance) that the order is ready and is given the procedure to collect it (Minor : 12320 - proximity: far)
- **Aisle promotion*** : in proximity to the beacon a passbook coupon is proposed to the user. (Minor : 12330 - proximity : near)
- **Music event info*** : a guide for a music festival is proposed to the user in proximity of beacon. A mobile web-page is used to display the interactive guide.  (Minor : 12340 - proximity : near)

