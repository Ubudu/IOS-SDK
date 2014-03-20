IOS-SDK
=======

### System and hardware requirements
For beacons related features
- IOS 7.0 or higher for supporting iBeacon features / IOS 7.1 recommended
- Iphone 4S/ Ipad 3rd generation or more recent
For Geofencing
- IOS 6.X or higher
- Iphone 4 or higher

## Adding the Ubudu SDK framework to your project

1. Copy UbuduIOSSDK.framework into your project directory and then drag & drop it into the Frameworks folder of your project in XCode
2. Add the following frameworks to your project :
  - QuartzCore.framework
  - CoreLocation.framework
  - CoreData.framework
  - CFNetwork.framework
  - SystemConfiguration.framework
  - MobileCoreServices.framework
  - MapKit.framework
  - PassKit.framework
  - libz.dylib

3. Check that these frameworks are also present
  - UIKit.framework
  - CoreGraphics.framework
  - Foundation.framework
Your framework folder should look like this :
![Framework list](__media-files/screenshots/ios_framework_list.png) 



