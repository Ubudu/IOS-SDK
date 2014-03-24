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

Starting to use the Ubudu SDK on IOS native app should be a 5 to 10 minutes process. Have a look at the demo app in the directory for a complete example. 

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
To start the SDK use the following code
```objective-c
    NSError *error = nil; 
    UbuduIOSSDK *sdk = [UbuduIOSSDK sharedInstance];
  BOOL started = [sdk start:&error];
    sdk.application = [UIApplication sharedApplication];
    sdk.delegate = self;
  if( !started ){
    //handle error 
  }
```
The delegate is the object which will be receiving all the notifications via callbacks defined in the **UbuduIOSSDKDelegate** protocol. This might be your current UIViewController subclass. 
The application is passed to the SDK so it can work correctly based on current application state (eg. sending local notifications when the application is in the background). If you don't set this or set it to nil the SDK will still work correctly when the host application is active. To support application's background mode the application reference needs to be passed to the SDK. Additionaly the resume function has to be called in application delegate for the SDK to correctly continue working if the host application was terminated. 
The sample resume call can look like this
```objective-c
  - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
  {
      NSError *error = nil;
      [[UbuduIOSSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];
    
    // Rest of app init code…
  }
 `
Calling **resume:launchOptions:error** method will not start the SDK if it wasn't expicitly started by **start:** call or it was stoppe by **stop** call.

When you want the SDK to stop working in the background call 

    UbuduIOSSDK *sdk = [UbuduIOSSDK sharedInstance];
  [sdk stop];

Stopping the SDK will stop it from updating location and tracking geofences.


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
Then still in the App delegate implement the callbacks that you would like to overwrite to handle the actions that have been programmed in the back-office.
There are 4 types of actions that can be executed when entering or exiting a zone : 
- Post to a server URL a callback : the server can than "decide" the next action of execute custom code (such as adding entries into a CRM, sending a push  notification or sending a push notification to a client). Note that the SDK will automatically take advantage of some wildcards that you can use to identify the actions in your callback. Example of URL : 'https://yourserver.com/push_event_to_app.json?event=exit&id={id}&udid={udid}'
- Trigger a local notification : a local notification can contain a message, notification type, a scheduled time and a custom payload see [Apple documentation](https://developer.apple.com/library/ios/documentation/iPhone/Reference/UILocalNotification_Class/Reference/Reference.html#//apple_ref/occ/instp/UILocalNotification/alertAction)
![Back-office configuration local notification](/__media-files/images/back_office_action_1.jpg) 
- Open a web-page in a web-view : note that the page can be either online (http or https) or in the application bundle (in this case use the file protocol in the URL)
![Back-office configuration open web view notification](/__media-files/images/back_office_action.jpg) 
- Open a passboook : note that the passbook can be either online (http or https) or in the application bundle (in this case use the file protocol in the URL)


### UbuduIOSSDKDelegate Callbacks


UbuduIOSSDK provides a couple of callback methods which can be used to override the SDK's default behaviour.

  - (void)ubuduIOSSDK_receivedOpenWebPageRequest:(NSURL *)url;
  
The **ubuduIOSSDK_receivedOpenWebPageRequest** is called when the SDK performs an action which should result in opening a web page on top of the current view. If you want to override (or disable) this behaviour implement the **ubuduIOSSDK_receivedOpenWebPageRequest** method in your delegate.
  
  - (void)ubuduIOSSDK_reveivedRegionNotification:(NSDictionary *)notificationData;

The **ubuduIOSSDK_reveivedRegionNotification** is called when the SDK performs an action which should only notify the delegate without performing any other actions.  
  
  - (void)ubuduIOSSDK_receivedLocalNotificationRequest:(UILocalNotification *)localNotification;

The **ubuduIOSSDK_receivedLocalNotificationRequest** is called when the SDK performs an action which should result in dispatching a local notification. If you want to override (or disable) this behaviour implement the **ubuduIOSSDK_receivedLocalNotificationRequest** method in your delegate.


  - (void)ubuduIOSSDK_receivedNewAdView:(UIView *)view;

The **ubuduIOSSDK_receivedNewAdView:** is called when the SDK receives new contents for the ad banner. 



Example of implementation of delegate methods in app : 
```objective-c
//AppDelegate.m

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    NSString *notifType = [notification.userInfo valueForKeyPath:@"payload.type"];

    // If the notification contains a custom payload that we want to handle
    // In this case we display a custom alert view instead of normal notification
    if ([notifType isEqualToString:@"order"])
    {
        [self displayOrderAwaitingAlert];
    }
    else
    {
        // Send back to the SDK the notification (that may have been received in background)
        // So it can trigger the right action (passbook or web view for example)
        [[UbuduIOSSDK sharedInstance] receiveLocalNotification:notification];
    }
}

#pragma mark - UbuduIOSSDK Delegate

- (void)ubuduIOSSDK_receivedOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedOpenWebPageRequest url = %@", url);
}

- (void)ubuduIOSSDK_receivedOpenPassbookRequest:(NSURL *)aPassbookUrl triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedOpenPassbookRequest aPassbookUrl = %@", aPassbookUrl);
}

- (void)ubuduIOSSDK_receivedRegionNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedRegionNotification notificationData = %@", notificationData);
}

- (void)ubuduIOSSDK_receivedSDKNotification:(NSDictionary *)notificationData triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedSDKNotification notificationData = %@", notificationData);
}

- (void)ubuduIOSSDK_receivedLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
    NSLog(@"ubuduIOSSDK_receivedLocalNotificationRequest localNotification = %@", localNotification);
    // Post notification only if it's a new one (avoid presenting multiple identical notification to the user)
    if ([[UDDemoManager sharedManager] hasLocalNotificationBeenTriggered:localNotification] == NO)
    {
        [[UDDemoManager sharedManager] markLocalNotificationAsTrigerred:localNotification];
        [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
    }
}

- (void)ubuduIOSSDK_receivedNewAdView:(UIView *)view triggeredBy:(UbuduIOSSDKTriggerSource)triggeredBy
{
//    NSLog(@"ubuduIOSSDK_receivedNewAdView view = %@", view);
}

- (void)ubuduIOSSDK_receivedErrorNotification:(NSError *)error
{
    if (error != nil) {
        NSLog(@"ubuduIOSSDK_receivedErrorNotification %@", error);
    }
}

// Debug callbacks
- (void)ubuduIOSSDK_receivedLocationChange:(CLLocation *)newLocation
{
//    NSLog(@"ubuduIOSSDK_receivedLocationChange newLocation = %@", newLocation);
}

- (void)ubuduIOSSDK_receivedEnterRegionNotification:(CLRegion *)region
{
//    NSLog(@"ubuduIOSSDK_receivedEnterRegionNotification region = %@", region);
}

- (void)ubuduIOSSDK_receivedExitRegionNotification:(CLRegion *)region
{
//    NSLog(@"ubuduIOSSDK_receivedExitRegionNotification region = %@", region);
}

- (void)ubuduIOSSDK_receivedDebugData:(id)data
{
//    NSLog(@"ubuduIOSSDK_receivedDebugData data = %@", data);
}

#pragma mark - Click & Collect Alert

- (void)displayOrderAwaitingAlert
{
    UIAlertView *alert = [[UIAlertView alloc] init];
    [alert setTitle:@"Your order"];
    [alert setMessage:@"Do you want to send your order to preparation now?"];
    [alert setDelegate:self];
    [alert addButtonWithTitle:@"No, I'll do it later"];
    [alert addButtonWithTitle:@"Yes"];
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        // No. Do nothing.
    } else if (buttonIndex == 1) {
        // Yes. Open order summary page.
        UIViewController * orderSummaryVC = [self.window.rootViewController.storyboard instantiateViewControllerWithIdentifier:@"UDOrderSummaryViewController"];
        [self.window.rootViewController presentViewController:orderSummaryVC animated:YES completion:nil];
    }
}
```
