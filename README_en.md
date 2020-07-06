[![Build Status](https://travis-ci.com/Coiney-SDK/CoineyKit-iOS.svg?token=q1fWSqJB3688yqHv3sZs&branch=master)](https://travis-ci.com/Coiney-SDK/CoineyKit-iOS)

# CoineyKit

Thanks for showing interest in CoineyKit. We work hard to make it as easy to integrate as possible, but if you have any issues at all, please create a ticket using our [Issue Tracker](https://github.com/Coiney-SDK/CoineyKit-iOS/issues).

## SDK E-money Payment Support Release (2020-07-07)

The STORES Terminal SDK (formerly CoineyKit) now supports e-money as a payment option. ※ The e-money payment option will not be available for semi-self and self-checkout systems.

**1. E-money payment guidelines**
- The transaction amount must be between 100 yen and 20,000 yen. 

- E-money payments cannot be refunded through the SDK. To refund an e-money payment, please refund via cash.

- Please install the STORES Terminal app to perform the following e-money operations: 
  - Checking the balance on a transit IC card (i.e. Suica, PASMO)
  - Checking the status of unconfirmed transactions. If a transaction ends in an unconfirmed state, please confirm the transaction status through the STORES Terminal app.

- The SDK does not support recharging the balance on a transit IC card.

- E-money payment support is only available for iOS SDK.


**2. Test accounts for development**

- We will be able to provide test accounts for development. If you are interested in working with test accounts, please let us know at stores_terminal_sdk@hey.jp.

**3. E-money payment precautions**
- For more details and precautions on integrating e-money payments in to your app, please contact us at the e-mail address above.

****

## Announcement: Service Name Change from Coiney to STORES Terminal ( 2020-04-27 )

Starting April 27, 2020, Coiney Inc. will change the name of its cashless store service, Coiney, to STORES Terminal.

The SDK will be renamed to "STORES Terminal SDK" in a future release, but the latest version of the SDK will continue to be available as "CoineyKit".

-------

# Example Application

## What we are going to create

If you follow along this tutorial you will learn how to create a basic application that allows the user to accept Credit Card payments using the Coiney Terminal.

You can find complete sample apps, written in Swift and Objective-C, in the `Example` folder.

## What you need

 This repository uses git-lfs. Please install it using homebrew or download it from here: <https://git-lfs.github.com>.

 * CoineyKit (Clone this repo after installing git-lfs.)
 * Xcode 10
 * Coiney Terminal; to purchase one, please contact us at <coineykitsupport@coiney.com>.

## Setting up your project

Begin by launching Xcode and creating a new project: `File → New → Project`. In the dialog that appears, Choose the `Single View Application` template. And enter project options as per the screenshot below.

![Template selection](.readme_images/template-selection.png)
![Template options](.readme_images/template-options.png)

Now that your project is created, copy the folder `CoineyKit` to your project folder, resulting in path of `<Your project folder>/CoineyKit` .

![Folder hierarchy](.readme_images/folder-hierarchy.png)

The next step is to add `CoineyKitResources.bundle`, `CoineyKit.xcconfig` & `CoineyKit.framework` to your project. (If you use git it's a good idea to add CoineyKit as a submodule, to make updating easier.)

Drag and drop `CoineyKit.xcconfig` and `CoineyKitResources.bundle` into the project navigator in Xcode.  Select "CoineyKit" as your Debug and Release configuration files.

![Configurations](.readme_images/configuration.png)

Go to your target's General settings, and add `CoineyKit.framework`and `TCMPayment.framework` to "Linked Frameworks and Libraries."

![Libraries and Frameworks](.readme_images/frameworks-libs2.png)

#### External Accessory Protocol for Coiney Terminal

For your app to connect to a Coiney Terminal for IC and magstripe transactions, we need to add `com.coiney.Coiney` to the list of supported accessory protocols.  Add the following to your `Info.plist` file:

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string>
</array>
```



## Initialization of SDK

Call the prepare method to initialize CoineyKit.
Please pass the ViewController that uses CoineyKit as an argument to the prepare method.
Note: Avoid calling the prepare method before the ViewController is displayed, as CoineyKit may not work properly. (i.e. Don't call the prepare method from viewDidLoad().)

### Objective-C

Open up `ViewController.m` and make it look like:

#### ViewController.m

```objective-c
(void)viewDidAppear:(BOOL)animated
{
  [super viewDidAppear:animated];

  [CYKit prepareInController:self];
}
```



### Swift

Open up `ViewController.swift` and make it look like:

#### ViewController.swift

```swift
override func viewDidAppear(_ animated: Bool) {
    super.viewDidAppear(animated)
    
    CYKit.prepare(in: self)
}
```


## Making our first payment

Open up `ViewController.h` and make it look like:

### Objective-C

#### ViewController.h

```objective-c
#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property(weak, nonatomic) IBOutlet UITextField *productMemoField, *productPriceField;

- (IBAction)makePayment:(id)aSender;
@end
```

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productMemoField.text;
    int price = [_productPriceField.text intValue];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:price memo:memo];

    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}
@end
```

### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {

    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!
    
    @IBAction func makePayment(sender: AnyObject) 
    {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
        // Create an instance of the Coiney payment controller. 
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        
        // Present it on top of the current controller.
        self.present(coineyController, animated: true, completion: nil)
    }
}
```

Now hook up a button to your `makePayment:` method, and text fields to `productNameField` & `productPriceField`.

![Action connection](.readme_images/action-connection.png)

If we run the application it should appear like below:

![App screenshot](.readme_images/simshot1.png)

Connect a terminal to make a transaction. Click the terminal information button on the right side of the navigation bar, and tap the  [Connect to Terminal] button.

## Get notified of the transaction status

To know the status of the transaction you simply make yourself the delegate of your Coiney controller, and it will notify you when a transaction is completed or canceled.

### Objective-C

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@interface ViewController () <CYCoineyViewControllerDelegate>
@end

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productNameField.text;
    NSInteger amount = [_productPriceField.text integerValue];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:amount memo:memo];
    coineyController.delegate = self;
    
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);
}

- (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController
{
    [aController dismissViewControllerAnimated:YES completion:nil];
    NSLog(@"Cancelled payment.");
}
@end
```

### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {

    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!

    @IBAction func makePayment(sender: AnyObject) {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
        // Create an instance of the Coiney payment controller.
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        coineyController.delegate = self
        
        // Present it on top of the current controller.
        self.present(coineyController, animated: true, completion: nil)
    }
}

extension ViewController : CYCoineyViewControllerDelegate {

    func coineyViewController(_ aController: CYCoineyViewController!,
                              didComplete aTransaction: CYTransaction!) {
        print("Completed transaction: \(aTransaction)")
    }

    func coineyViewControllerDidCancel(_ aController: CYCoineyViewController!) {
        self.dismiss(animated: true, completion: nil)
        print("Cancelled payment.")
    }
}
```

## Show the details of a transaction

You can use a transaction ID to bring up its detail view.  The view can contain a refund button if refunding should be allowed.

The refund button will be disabled in the following cases:

* `allowRefunding:NO` was passed
* You are logged in with a staff account (only owners and managers can refund)
* The transaction is already refunded

Refunding is not allowed for transactions 60 days and older.  Attemping to refund such a transaction results in an error alert being shown.

### Objective-C

#### ViewController.m

```objective-c
#import "ViewController.h"
@import CoineyKit;

@interface ViewController () <CYCoineyViewControllerDelegate>
@end

@implementation ViewController

- (IBAction)makePayment:(id)aSender
{
    NSString *memo = _productNameField.text;
    NSInteger amount = [_productPriceField.text integerValue];

    // Create an instance of the Coiney payment controller.
    CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithAmount:amount memo:memo];
    coineyController.delegate = self;
    
    // Present it on top of the current controller.
    [self presentViewController:coineyController animated:YES completion:nil];
}

- (void)coineyViewController:(CYCoineyViewController *)aController
      didCompleteTransaction:(id<CYTransaction>)aTransaction
{
    NSLog(@"Completed transaction: %@", aTransaction);
    
    [aController dismissViewControllerAnimated:YES completion:^{
        CYTransactionViewController *transactionViewController =
            [CYTransactionViewController transactionViewControllerWithTransaction:aTransaction
                                                                   allowRefunding:YES];
                                                          // Pass NO to disable the refund button
        transactionViewController.navigationItem.rightBarButtonItem =
        [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                          target:self
                                                          action:@selector(done:)];
        UINavigationController *navigationController =
            [[UINavigationController alloc] initWithRootViewController:transactionViewController];
        [navigationController setModalPresentationStyle:UIModalPresentationFormSheet];
        [self presentViewController:navigationController
                           animated:YES
                         completion:nil];
     }];
}

- (void)done:(id)aSender
{
	[self dismissViewControllerAnimated:YES completion:nil];
}
@end
```

### Swift

#### ViewController.swift

```swift
import UIKit
import CoineyKit

class ViewController: UIViewController {
    
    @IBOutlet weak var memoField: UITextField!
    @IBOutlet weak var amountField: UITextField!

    @IBAction func makePayment(sender: AnyObject) {
        let memo = productNameField.text ?? ""
        let amount = Int64(productPriceField.text!) ?? 0
        
        // Create an instance of the Coiney payment controller.
        guard let coineyController = CYCoineyViewController.init(amount: amount, memo: memo) else {
            fatalError("Failed to initialize CYCoineyViewController.")
        }
        coineyController.delegate = self
        
        // Present it on top of the current controller.
        self.present(coineyController, animated: true, completion: nil)
    }
    
    func done() {
    	self.dismiss(animated: true, completion: nil)
    }
}

extension ViewController : CYCoineyViewControllerDelegate {

    func coineyViewController(_ aController: CYCoineyViewController!,
                              didComplete aTransaction: CYTransaction!) {
        print("Completed transaction: \(aTransaction)")
        
        self.dismiss(animated: true, completion: {
            guard let transactionViewController =
                CYTransactionViewController.init(transaction: aTransaction, allowRefunding: true) else {
                    // Pass "allowRefunding: false" to disable refunding
                    fatalError("Failed to initialize CYTransactionViewController.")
            }
            
            transactionViewController.navigationItem.rightBarButtonItem =
                UIBarButtonItem.init(barButtonSystemItem: .done,
                                     target: self,
                                     action: #selector(self.done))
            
            let navigationController = UINavigationController.init(rootViewController: transactionViewController)
            navigationController.modalPresentationStyle = .formSheet
            self.present(navigationController, animated: true, completion: nil)
        })
    }
}
```

After making a payment and tapping Done, you will see a `CYTransactionViewController` showing the details of the transaction.

![App screenshot](.readme_images/simshot3.png)

## Looking up a transaction

You can use a transaction's unique identifier to query the corresponding CYTransaction object, and show it in a view controller.

### Objective-C

```objective-c
CYLookUpTransaction(transactionIdentifier, ^(id<CYTransaction> transaction, NSError *err) {
    if(transaction)
        NSLog(@"Transaction found: %@", transaction);
        CYTransactionViewController *transactionViewController =
            [CYTransactionViewController transactionViewControllerWithTransaction:transaction
                                                                   allowRefunding:YES]; // Pass NO to hide the refund button
                                                                      
        transactionViewController.navigationItem.rightBarButtonItem =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone   
                                                          target:self
                                                          action:@selector(done:)];
        UINavigationController *navigationController = [UINavigationController new];
        navigationController.viewControllers = @[transactionViewController];
        [navigationController setModalPresentationStyle:UIModalPresentationFormSheet];
        [self presentViewController:navigationController animated:YES completion:nil];
    }
    else
        NSLog(@"Transaction not found: %@", err);
});

...

- (void)done:(id)aSender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}
```

### Swift

```swift
CYLookUpTransaction(transactionIdentifier, { aTransaction, aError in
    if let transaction = aTransaction {
        guard let transactionViewController =
            CYTransactionViewController.init(transaction: transaction, allowRefunding: true) else {
                fatalError("Failed to initialize CYTransactionViewController.")
        }
        
        transactionViewController.navigationItem.rightBarButtonItem =
            UIBarButtonItem.init(barButtonSystemItem: .done,
                                 target: self,
                                 action: #selector(self.done))
        
        let navigationController = UINavigationController.init(rootViewController: transactionViewController)
        navigationController.modalPresentationStyle = .formSheet
        self.present(navigationController, animated: true, completion: nil)
    } else if let error = aError {
        print("Transaction not found: \(error)")
    }
})

...

func done() {
    self.dismiss(animated: true, completion: nil)
}
```

Please make sure you are authenticated before calling `CYLookUpTransaction`, by using `+[CYAuthenticationViewController CYCheckAuthenticationStatus:inViewController:]` as follows:

```objective-c
[CYCheckAuthenticationStatus:^{
    CYLookUpTransaction(...
    ...
}
inViewController:viewController];
```

## Receipt Printing

By enabling printing in CoineyKit, paper receipts can be printed at the receipt and transaction detail views.  Printing is disabled by default.  Follow these steps to use CoineyKit's receipt printing feature:

1. Call `CYEnablePrinting(YES)`, typically at app launch, in `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]`.
2. Add the following External Accessory protocols to your Info.plist.

```xml
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string><!--M010 Card Reader-->
  <string>com.sii-ps.siieap</string>
  <string>com.epson.escpos</string>
  <string>jp.star-m.starpro</string>
</array>
```

3. Pair your iPhone or iPad with a supported printer through the Bluetooth system settings.  See coiney.com for a list of supported printers.
4. Make a transaction to get to the receipt view.  You will see a [Print Receipt] button.

Note: If you plan to implement receipt printing in your own app, do not call `CYEnablePrinting(YES)`, since the printer's `EASession` cannot be shared.

## Submitting Your App for Review

When submitting your app for review through iTunes Connect, you will need an MFi PPID (Made for iPhone Product Plan ID) for interoperation with the Miura M010.  Please use the form [here](../../wiki/PPID-の申請) to request your PPID.

## And that's it!

If you have any further questions feel free to email <coineykitsupport@coiney.com>.
