Pod::Spec.new do |s|
  s.name         = "UbuduSDK"
  s.version      = "1.15"
  s.summary      = "Add support of cloud-managed geofence and beacon proximity triggered interactions to IOS 7+ applications. Works with any iBeacon device."
  s.homepage     = "https://github.com/Ubudu/IOS-SDK"
  s.license      = { :type => "BSD", :file => "LICENSE" }
  s.author       = { "Ubudu SAS" => "cocoapods@ubudu.com" }
  s.social_media_url = "https://twitter.com/Ubudu"

  s.platform     = :ios, "6.0"
  s.source       = { :git => "https://github.com/Ubudu/IOS-SDK.git", :tag => "v1.15" }
  s.vendored_frameworks = "UbuduSDK.framework"
  s.frameworks = "Foundation", "CoreGraphics", "UIKit", "SystemConfiguration", "MobileCoreServices", "CoreData", "CoreLocation", "CoreBluetooth", "PassKit"
  s.libraries = "z"

  s.requires_arc = true
  s.xcconfig = { "OTHER_LDFLAGS" => "-ObjC -all_load" }
end
