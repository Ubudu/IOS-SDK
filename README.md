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
![Framework list](/__media-files/images/ios_framework_list.jpg) 

4. Go to Target -> Other Linker Flags and add the following flags:
`-ObjC -all_load
![Linker flag](/__media-files/images/ios_linker_flags.jpg) 

5. In your Info.plist add the "location" capability to the "Required background modes" section. In case you plan to use Maps or Passbook in your proximity aware app don't forget also to enable these capabilities. You can do this in the general settings of your project :
![Capabilities](/__media-files/images/ios_capabilities.jpg) 

## Starting and hooking to the Ubudu SDK
Consider the example below which is used in our demo-app which demonstrate 3 different usages of the SDK in scenarios.
1. Start the SDK in AppDelegate.m of your application

To Start the SDK :
```objective-c
/* AppDelegate.m */
#import <UbuduIOSSDK/UbuduIOSSDK.h>
...
@implementation UDAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  //...start initilializations

  // You can perform this task where you want to start the SDK 
  [self initUbuduSDK];

  //Mandatory in didFinishLaunchingWithOptions
  NSError * error = nil;
  [[UbuduIOSSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];

  //...finish initializations

}

#pragma mark - UbuduSDK

/**
 *
 */
 - (void)initUbuduSDK
{
    NSError *error;
    BOOL deviceSupportsGeofences = [UbuduIOSSDK deviceSupportsGeofences:[UIDevice currentDevice] error:&error];
    BOOL deviceSupportsBeacons = [UbuduIOSSDK deviceSupportsBeacons:[UIDevice currentDevice] error:&error];
    
    if ([[UbuduIOSSDK sharedInstance] isRunning] == NO && deviceSupportsBeacons && deviceSupportsGeofences) {
        NSError *error = nil;
        UbuduIOSSDK *sdk = [UbuduIOSSDK sharedInstance];
        [sdk setUseNamespace:@"ff356b88057340a771e9b072d16278829c67b9a1"];
        [sdk setApplication:[UIApplication sharedApplication]];
        /** optional store in the ext_id id field a specific identifier used by the application to identify user
        [sdk setUser:[[UbuduIOSSDKUser alloc] initWithID:nil withProperties:@{@"ext_id": kUDDefaultClientName}]];
        */
        BOOL started = [[UbuduIOSSDK sharedInstance] start:&error];
        if (!started) {
            NSLog(@"UbuduSDK start error: %@", error);
        }
    }
}
  ```

The namespace value i.e. `ff356b88057340a771e9b072d16278829c67b9a1` in the example above is the namespace UID of the application creatd in the [Back-office manager web interface](https://manager.ubudu.com) of your application. 
When you access the Back-office web interface in the details of the application you created you will find an example of integration with the correct UID for your application.
The demo application provided in the folder will 
