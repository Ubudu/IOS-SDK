IOS-SDK
=======
Ubudu contextual interactions SDK for IOS.

### System and hardware requirements
For beacons related features:
- IOS 7.0 or higher for supporting iBeacon features / IOS 7.1 recommended
- Iphone 4S / Ipad 3rd generation or more recent

For geofencing:
- IOS 6.0 or higher
- Iphone 4 or higher

## Adding the Ubudu SDK framework to your project

Starting to use the Ubudu SDK on IOS native app should be a 5 to 10 minutes process. Have a look at the demo app in the directory for a complete example. 

1. Copy UbuduSDK.framework into your project directory and then drag & drop it into the Frameworks folder of your project in XCode.

2. Add the following frameworks to your project if their are not already present:
  - CoreLocation.framework
  - CoreData.framework
  - PassKit.framework
  - SystemConfiguration.framework
  - MobileCoreServices.framework
  - libz.dylib

  Your framework folder should look like this:

  ![Framework list](/__media-files/images/ios_frameworks_list.png) 

3. Go to Your Target -> "Build Settings" tab -> "Other Linker Flags" and add the following flags: *-ObjC -all_load*

  ![Linker flag](/__media-files/images/ios_linker_flags.png) 

4. In your Info.plist add the "location" capability to the "Required background modes" section. In case you plan to use Maps or Passbook in your proximity aware app don't forget also to enable these capabilities. You can do this in the general settings of your project:

  ![Capabilities](/__media-files/images/ios_capabilities.png) 


## Starting and hooking to the Ubudu SDK

To start the SDK use the following code:

```objective-c
NSError *error = nil;
[UbuduSDK sharedInstance].appNamespace = @"634b207ee2f313c109c58675b44324ac2d41e61e";
[UbuduSDK sharedInstance].delegate = self;
BOOL started = [[UbuduSDK sharedInstance] start:&error];
if (!started) {
    NSLog(@"UbuduSDK start error: %@", error);
    // Handle error
}
```

The delegate is the object which will be receiving all the notifications via callbacks defined in the **UbuduSDKDelegate** protocol. This might be your AppDelegate or your current UIViewController subclass.
The application is passed to the SDK so it can work correctly based on current application state (eg. sending local notifications when the application is in the background). If you don't set this or set it to nil the SDK will still work correctly when the host application is active. To support application's background mode the application reference needs to be passed to the SDK. Additionaly the resume function has to be called in application delegate for the SDK to correctly continue working if the host application was terminated. 
The sample resume call can look like this

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSError *error = nil;
    [[UbuduSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];
  
    // Rest of app init code…
}
```

Calling **resume:launchOptions:error** method will not start the SDK if it wasn't expicitly started by **start:** call or it was stopped by **stop** call.

When you want the SDK to stop working in the background call 
```objective-c
[[UbuduSDK sharedInstance] stop];
```
Stopping the SDK will stop it from updating location and tracking geofences.


Full example on how to initialize and start the SDK:
```objective-c
/* AppDelegate.m */
#import <UbuduSDK/UbuduSDK.h>

@implementation UDAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  // Mandatory in didFinishLaunchingWithOptions, restores the SDK state
  NSError *error = nil;
  [[UbuduSDK sharedInstance] resume:application launchOptions:launchOptions error:&error];
  if (error != nil) {
      NSLog(@"UbuduSDK resume error: %@", error);
  }

  // You can perform this task where you want to start the SDK, but the AppDelegate is a good choice
  [self initUbuduSDK];

  //...finish app initialization
}

- (void)initUbuduSDK
{
    if ([[UbuduSDK sharedInstance] isRunning] == NO) {
        NSError *error = nil;
        [UbuduSDK sharedInstance].appNamespace = @"634b207ee2f313c109c58675b44324ac2d41e61e";
        [UbuduSDK sharedInstance].delegate = self;
        /** optionally, provide the ID of your user so we can link the Ubudu user with the IDs of your information system. */
        //[UbuduSDK sharedInstance].user = [[UbuduUser alloc] initWithID:@"Your client ID" withProperties:@{@"foo_property":@"bar_value"}];
        BOOL started = [[UbuduSDK sharedInstance] start:&error];
        if (!started) {
            NSLog(@"UbuduSDK start error: %@", error);
            // Handle error
        }
    }
}
```

The namespace value i.e. `634b207ee2f313c109c58675b44324ac2d41e61e` in the example above is the namespace UID of the application creatd in the [back-office manager web interface](https://manager.ubudu.com) of your application. 
When you access the back-office web interface in the details of the application you created you will find an example of integration with the correct UID for your application.
Then still in the App delegate implement the callbacks that you would like to overwrite to handle the actions that have been programmed in the back-office.
There are 4 types of actions that can be executed when entering or exiting a zone : 
- Post to a server URL a callback : the server can than "decide" the next action or execute custom code (such as adding entries into a CRM, sending a push notification or sending a push notification to a client). Note that the SDK will automatically take advantage of some wildcards that you can use to identify the actions in your callback. Example of URL : 'https://yourserver.com/push_event_to_app.json?event=exit&udid={udid}'.
- Trigger a local notification : a local notification can contain a message, notification type, a scheduled time and a custom payload see [Apple documentation](https://developer.apple.com/library/ios/documentation/iPhone/Reference/UILocalNotification_Class/Reference/Reference.html#//apple_ref/occ/instp/UILocalNotification/alertAction).
![Back-office configuration local notification](/__media-files/images/back_office_action_1.jpg) 
- Open a web-page in a web-view : note that the page can be either online (http or https) or in the application bundle (in this case use the file protocol in the URL).
![Back-office configuration open web view notification](/__media-files/images/back_office_action.jpg) 
- Open a passbook: note that the pass can be either online (http or https) or in the application bundle (in this case use the file protocol in the URL).


### UbuduSDKDelegate Callbacks


UbuduSDK provides a couple of callback methods which can be used to override the SDK's default behaviour.

```objective-c
  - (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy;
```

The **ubudu:executeOpenWebPageRequest:triggeredBy:** is called when an action which should result in opening a web page on top of the current view should happen.
If you want to override the behaviour of this action implement the **ubudu:executeOpenWebPageRequest:triggeredBy:** method in your delegate.

```objective-c
  - (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy;
```

The **ubudu:executeOpenPassbookRequest:triggeredBy:** is called when an action which should result in presenting a passbook pass to the user should happen.
If you want to override the behaviour of this action implement the **ubudu:executeOpenPassbookRequest:triggeredBy:** method in your delegate.
  
```objective-c
  - (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy;
```

The **ubudu:executeLocalNotificationRequest:triggeredBy:** is called when the SDK performs an action which should result in dispatching a local notification.
If you want to override this behaviour implement the **ubudu:executeLocalNotificationRequest:triggeredBy:** method in your delegate.

```objective-c
  - (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveNewAdView:(UIView *)view triggeredBy:(UbuduTriggerSource)triggeredBy;
```

The **ubudu:didReceiveNewAdView:triggeredBy:** is called when the SDK receives new contents for the ad banner.



Example of implementation of Ubudu SDK delegate methods:
```objective-c
//AppDelegate.m

#pragma mark - UbuduSDKDelegate

- (BOOL)ubudu:(UbuduSDK *)ubuduSDK shouldExecuteLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy
{
    NSLog(@"Ubudu shouldExecuteLocalNotificationRequest);
    // Post notification only if it's a new one (avoid presenting multiple identical notification to the user)
    BOOL hasBeenTriggered = [[Manager sharedManager] hasLocalNotificationBeenTriggered:localNotification.alertBody];
    return (hasBeenTriggered == NO);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK executeLocalNotificationRequest:(UILocalNotification *)localNotification triggeredBy:(UbuduTriggerSource)triggeredBy
{
    NSLog(@"Ubudu executeLocalNotificationRequest localNotification = %@", localNotification);
    [[Manager sharedManager] markLocalNotificationAsTrigerred:localNotification];
    [[UIApplication sharedApplication] presentLocalNotificationNow:localNotification];
}

// Uncomment the following methods to use a custom implementation of the corresponding action

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenWebPageRequest:(NSURL *)url triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    NSLog(@"Ubudu executeOpenWebPageRequest url = %@", url);
//}

//- (void)ubudu:(UbuduSDK *)ubuduSDK executeOpenPassbookRequest:(NSURL *)passbookUrl triggeredBy:(UbuduTriggerSource)triggeredBy
//{
//    NSLog(@"Ubudu executeOpenPassbookRequest passbookUrl = %@", passbookUrl);
//}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveNewAdView:(UIView *)view triggeredBy:(UbuduTriggerSource)triggeredBy;
{
    NSLog(@"Ubudu didReceiveNewAdView view = %@", view);
}

- (void)ubudu:(UbuduSDK *)ubuduSDK didReceiveErrorNotification:(NSError *)error;
{
    NSLog(@"Ubudu didReceiveErrorNotification error = %@", error);
}

#pragma mark - Local Notifications

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    NSString *notifType = [notification.userInfo valueForKeyPath:@"payload.type"];

    // If the notification contains a custom payload that we want to handle
    if ([notifType isEqualToString:@"order"]) {
        // In this case we display a custom alert view instead of posting the notification
        [self displayOrderAwaitingAlert:@"Do you want to send your order to preparation now?"];
    } else {
        // Send back to the SDK the notification (that may have been received in background)
        // So it can trigger the right action (passbook or web view for example)
        [[UbuduSDK sharedInstance] receiveLocalNotification:notification];
    }
}

#pragma mark - Click & Collect Alert

- (void)displayOrderAwaitingAlert:(NSString *)message
{
    UIAlertView *alert = [[UIAlertView alloc] init];
    [alert setTag:kAlertTagClickAndCollect];
    [alert setTitle:@"Your order"];
    [alert setMessage:message];
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
        UIViewController *orderSummaryVC = [self.window.rootViewController.storyboard instantiateViewControllerWithIdentifier:@"UDOrderSummaryViewController"];
        [self.window.rootViewController presentViewController:orderSummaryVC animated:YES completion:nil];
    }
}
```

### Users segmentation - Tags

If you want to target only a subset of your users, it is possible to associate arbitrary tags to them.
Then you define the conditions that must or must not be met for your rules and actions to trigger.

You can define the conditions for a beacon or geofence rule in the back-office, from the beacon and geofence edition page.

![Capabilities](/__media-files/images/back_office_target_user_segments.png)

Once you have defined your conditions in the back-office, you need to assign tags to your mobile users using the Ubudu iOS SDK.
This is very simple and is done typically before starting the SDK, as following:

```objective-c
[UbuduSDK sharedInstance].appNamespace = @"634b207ee2f313c109c58675b44324ac2d41e61e";
[UbuduSDK sharedInstance].delegate = self;
[UbuduSDK sharedInstance].user = [[UbuduUser alloc] initWithID:@"your_user_id" withProperties:@{@"foo_property": @"bar_value"} tags:@[@"female", @"under_40"]];

NSError *error = nil;
BOOL started = [[UbuduSDK sharedInstance] start:&error];
if (started == NO) {
  // Handle error
}
```

If you need to update the tags of your user once the SDK has been started, just re-assign the tags property of the user, and the SDK will automatically send the updated data to the back-office.

```objective-c
// Could be called if the user changes his age in the settings for example
[UbuduSDK sharedInstance].user.tags = @[@"female", @"under_25"];
```
