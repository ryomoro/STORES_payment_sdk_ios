import UIKit
import CoineyKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
    
    var window: UIWindow?
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        CYEnablePrinting(true)
        CYKit.setEnableSendReceipt(true)
        return true
    }
}

