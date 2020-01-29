//
//  AppDelegate.swift
//  proximitySDKSwiftSample
//
//  Created by zioolek on 24/01/2020.
//  Copyright © 2020 ubudu. All rights reserved.
//

import UIKit
import UbuduSDKSwift
import CoreLocation
import UserNotifications

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        setupUbuduSDK()
        setupNotifications()
        return true
    }

    // MARK: UISceneSession Lifecycle

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }


}

extension AppDelegate: UNUserNotificationCenterDelegate {
        
    // The method will be called on the delegate only if the application is in the foreground. If the method is not implemented or the handler is not called in a timely manner then the notification will not be presented. The application can choose to have the notification presented as a sound, badge, alert and/or in the notification list. This decision should be based on whether the information in the notification is otherwise visible to the user.
    func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
        completionHandler(UNNotificationPresentationOptions.alert)
    }
    
    // The method will be called on the delegate when the user responded to the notification by opening the application, dismissing the notification or choosing a UNNotificationAction. The delegate must be set before the application returns from application:didFinishLaunchingWithOptions:.
    func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
        guard let sdk = UbuduSDK.sharedInstance() else { return }
        sdk.executeNotificationRequestActions(response.notification.request)
        completionHandler()
    }
}

extension AppDelegate {
    func setupUbuduSDK() {
        guard let sdk = UbuduSDK.sharedInstance() else { return }
        sdk.appNamespace = "1fe729c967a0a20a0490402adcf585b781181d88"

        sdk.beaconsEnabled                      = true
        sdk.geofencesEnabled                    = false
        sdk.isFileLogEnabled                    = false
        sdk.useExtendedBackgroundRangingTime    = false

        sdk.delegate = self

        do {
            try sdk.start()
        } catch let error {
            print("error: \(error) while starting Ubudu SDK")
        }
    }
    
    func setupNotifications() {
        let currentNC = UNUserNotificationCenter.current()
        currentNC.delegate = self
        currentNC.requestAuthorization(options: [.alert, .badge, .sound]) { granted, error in
            print("Notification center authorization request completion. granted: \(granted) error: \(String(describing: error))")
        }
    }
}

// MARK - Ubudu SDK delegate
extension AppDelegate: UbuduSDKDelegate {

    func ubudu(_ ubuduSDK: UbuduSDK!, didReceiveEnterRegionNotification region: CLRegion!) {
        print("\(#function) region: \(String(describing: region))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didReceiveExitRegionNotification region: CLRegion!) {
        print("\(#function) region \(String(describing: region))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, shouldExecute notificationRequest: UNNotificationRequest!, triggeredBy trigger: UbuduTriggerSource) -> Bool {
        return true
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, shouldExecuteOpenWebPageRequest url: URL!, triggeredBy trigger: UbuduTriggerSource) -> Bool {
        return true
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didFindNewBeacon beaconName: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) beaconName: \(String(describing: beaconName))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didUpdateBeacon beaconName: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) beaconName: \(String(describing: beaconName)) userInfo: \(String(describing: userInfo))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didReceivePingFromBeacon beaconName: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) beaconName: \(beaconName), userInfo: \(String(describing: userInfo))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didLoseBeaconSignal beaconName: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) region: \(String(describing: beaconName)), userInfo: \(String(describing: userInfo))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didEnterBeaconRegion regionUUID: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) region: \(String(describing: regionUUID)), userInfo: \(String(describing: userInfo))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, didExitBeaconRegion regionUUID: String!, userInfo: [AnyHashable : Any]! = [:]) {
        print("\(#function) region: \(String(describing: regionUUID)), userInfo: \(String(describing: userInfo))")
    }

    func ubudu(_ ubuduSDK: UbuduSDK!, execute notificationRequest: UNNotificationRequest!, triggeredBy trigger: UbuduTriggerSource) {
        print("\(#function) notification request: \(notificationRequest.description) title: \(notificationRequest.content.title) body: \(notificationRequest.content.body)")
    }
}
