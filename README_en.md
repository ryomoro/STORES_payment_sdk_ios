# CoineyKit

Thanks for showing interest in CoineyKit. We work hard to make it as easy to integrate as possible, but if you have any issues at all, please create a ticket using our [Issue Tracker](https://github.com/Coiney-SDK/CoineyKit-iOS/issues).

-------

# Example Application

## What we are going to create

If you follow along this tutorial, you will learn how to create a basic application, that allows the user to accept Credit Card payments using the Coiney Terminal.

You can find a complete sample app at `Example/Coiney Test.xcodeproj`.

## What you need

 This repository uses git-lfs. Please install it using homebrew or download it from here: https://git-lfs.github.com.

 * CoineyKit
 * Xcode 7 or above (Installed in `/Applications`)
 * Coiney Terminal; to purchase one, please contact us at <coineykit-support@coiney.com>.

## Setting up your project

Begin by launching Xcode and creating a new project: `File → New → Project`. In the dialog that appears, Choose the `Single View Application` template. And enter project options as per the screenshot below.

![Template selection](.readme_images/template-selection.png)
![Template options](.readme_images/template-options.png)

Now that your project is created, copy the folder `CoineyKit` to your project folder, resulting in path of `<Your project folder>/CoineyKit` .

![Folder hierarchy](.readme_images/folder-hierarchy.png)

The next step is to add `CoineyKitResources.bundle`, `CoineyKit.xcconfig` & `CoineyKit.framework` to your project. (If you use git it's a good idea to add CoineyKit as a submodule, that way you'll always know if it is up to date or not)

Drag and drop `CoineyKit.xcconfig` and `CoineyKitResources.bundle` into the project navigator in Xcode.  Select "CoineyKit" as your Debug and Release configuration files.

![Configurations](.readme_images/configuration.png)

Go to your target's General settings, and add `CoineyKit.framework`, as well as the following:

 * libstdc++.tbd
 * libsqlite3.tbd

![Libraries and Frameworks](.readme_images/frameworks-libs.png)

Now you're almost ready to make use of CoineyKit, you just need to update your build settings to use CoineyKit.xcconfig, as shown in the above screenshot.

#### External Accessory Protocol for Coiney Terminal

For your app to connect to a Coiney Terminal for IC and magstripe transactions, we need to add `com.coiney.Coiney` to the list of supported accessory protocols.  Add the following to your `Info.plist` file:

```
<key>UISupportedExternalAccessoryProtocols</key>
<array>
  <string>com.coiney.Coiney</string>
</array>
```

## Making our first payment

Open up `ViewController.h` and make it look like:

### Objective-C

#### ViewController.h

    #import <UIKit/UIKit.h>
    
    @interface ViewController : UIViewController
    @property(weak, nonatomic) IBOutlet UITextField *productMemoField, *productPriceField;
    
    - (IBAction)makePayment:(id)aSender;
    @end

#### ViewController.m

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

### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit
    
    class ViewController: UIViewController {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
        
        @IBAction func makePayment(sender: AnyObject) {
            let amount: Int64? = amountField == nil ? nil : Int64(amountField!.text!)
            if (amount != nil) {
                let coineyController: CYCoineyViewController = CYCoineyViewController(amount: amount, memo: memo)
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    }
    
Now hook up a button to your `makePayment:` method, and text fields to `productNameField` & `productPriceField`.

![Action connection](.readme_images/action-connection.png)

If we run the application it should appear like below:

![App screenshot](.readme_images/simshot1.png)

Connect a terminal to make a transaction. Click the terminal information button on the right side of the navigation bar, and tap the  [Connect to Terminal] button.

## Get notified of the transaction status

To know the status of the transaction you simply make yourself the delegate of your Coiney controller, and it will notify you when a transaction is completed or canceled.

### Objective-C

#### ViewController.m

    #import "ViewController.h"
    @import CoineyKit;
    
    @interface ViewController () <CYCoineyViewControllerDelegate>
    @end
    
    @implementation ViewController
    
    - (IBAction)makePayment:(id)aSender
    {
        // Create a line item to pre-populate the Coiney controller with.
        NSString *memo = _productMemoField.text;
        NSInteger price = [_productPriceField.text integerValue];
        
        CYItem *item = [CYItem itemWithTotal:price
                                    currency:CYCurrencyJPY
                                        memo:memo];
        
        // Create an instance of the Coiney payment controller.
        CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[item]];
        coineyController.delegate = self;
        // Present it on top of the current controller.
        [self presentViewController:coineyController animated:YES completion:nil];
    }
    
    - (void)coineyViewController:(CYCoineyViewController *)aController
          didCompleteTransaction:(id<CYTransaction>)aTransaction
    {
        NSLog(@"Completed transaction!: %@", aTransaction);
    }
    
    - (void)coineyViewControllerDidCancel:(CYCoineyViewController *)aController
    {
        [aController dismissViewControllerAnimated:YES completion:nil];
        NSLog(@"Cancelled payment.");
    }
    @end

### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit

    class ViewController: UIViewController, CYCoineyViewControllerDelegate {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
    
        @IBAction func makePayment(sender: AnyObject) {
            let amount: UInt? = amountField == nil ? nil : UInt(amountField!.text!)
            if (amount != nil) {
                let item: CYItem = CYItem(total: amount!, currency: .JPY, memo: memoField?.text)
                let coineyController: CYCoineyViewController = CYCoineyViewController(lineItems: [item])
                coineyController.delegate = self
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    
        func coineyViewController(aController: CYCoineyViewController!,
             didCompleteTransaction aTransaction: CYTransaction!) {
            print("Completed transaction: \(aTransaction)")
        }
    
        func coineyViewControllerDidCancel(aController: CYCoineyViewController!) {
            self.dismissViewControllerAnimated(true, completion: nil)
            print("Cancelled")
        }
    }
    
## Show the details of a transaction

You can use a transaction ID to bring up its detail view.  The view can contain a refund button if refunding should be allowed.

The refund button will be hidden in the following cases:

* `allowRefunding:NO` was passed
* You are logged in with a staff account (only owners and managers can refund)
* The transaction is already refunded

### Objective-C

#### ViewController.m

    #import "ViewController.h"
    @import CoineyKit;
    
    @interface ViewController () <CYCoineyViewControllerDelegate>
    @end
    
    @implementation ViewController
    
    - (IBAction)makePayment:(id)aSender
    {
        // Create a line item to pre-populate the Coiney controller with.
        NSString *memo = _productMemoField.text;
        int price = [_productPriceField.text intValue];
        
        CYItem *item = [CYItem itemWithTotal:price
                                        currency:CYCurrencyJPY
                                            memo:memo];
        
        // Create an instance of the Coiney payment controller.
        CYCoineyViewController * coineyController = [[CYCoineyViewController alloc] initWithLineItems:@[item]];
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
                                                              // Pass NO to hide the refund button
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

### Swift

#### ViewController.swift

    import UIKit
    import CoineyKit

    class ViewController: UIViewController, CYCoineyViewControllerDelegate {
        @IBOutlet var memoField: UITextField?
        @IBOutlet var amountField: UITextField?
    
        @IBAction func makePayment(sender: AnyObject) {
            let amount: UInt? = amountField == nil ? nil : UInt(amountField!.text!)
            if (amount != nil) {
                let item: CYItem = CYItem(total: amount!, currency: .JPY, memo: memoField?.text)
                let coineyController: CYCoineyViewController = CYCoineyViewController(lineItems: [item])
                coineyController.delegate = self
                self.presentViewController(coineyController, animated: true, completion: nil)
            }
        }
    
        func coineyViewController(aController: CYCoineyViewController!,
            didCompleteTransaction aTransaction: CYTransaction!) {                                
            self.dismissViewControllerAnimated(true) { () -> Void in
                let transactionController = CYTransactionViewController(transaction: aTransaction,
                    allowRefunding: true)
                transactionController.navigationItem.rightBarButtonItem =
                    UIBarButtonItem(barButtonSystemItem: .Done, target: self, action: "done")
                let navigationController = UINavigationController(rootViewController: transactionController)
                navigationController.modalPresentationStyle = .FormSheet
                self.presentViewController(navigationController, animated: true, completion: nil)
            }
        }
    
        func done() {
            self.dismissViewControllerAnimated(true, completion: nil)
        }
    }

After making a payment and tapping Done, you will see a `CYTransactionViewController` showing the details of the transaction.

![App screenshot](.readme_images/simshot3.png)

## Looking up a transaction

You can use a transaction's unique identifier to query the corresponding CYTransaction object, and show it in a view controller.

### Objective-C

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

### Swift

    CYLookUpTransaction(transactionIdentifier, { (transaction, error) -> Void in
        if error != nil {
            print("Transaction not found: \(error)")
        } else {
            let transactionController = CYTransactionViewController(transaction: transaction, allowRefunding: true)
            transactionController.navigationItem.rightBarButtonItem =
                UIBarButtonItem(barButtonSystemItem: .Done, target: self, action: "done")
            let navigationController = UINavigationController(rootViewController: transactionController)
            navigationController.modalPresentationStyle = .FormSheet
            self.presentViewController(navigationController, animated: true, completion: nil)
        }
    })
    
    ...
    
    func done() {
        self.dismissViewControllerAnimated(true, completion: nil)
    }

## Receipt Printing

By enabling printing in CoineyKit, paper receipts can be printed at the receipt and transaction detail views.  Printing is disabled by default.  Follow these steps to use CoineyKit's receipt printing feature:

1. Call `CYEnablePrinting(YES)`, typically at app launch, in `-[UIApplicationDelegate application:didFinishLaunchingWithOptions:]`.
2. Pair your iPhone or iPad with a supported printer through the Bluetooth system settings.  See coiney.com for a list of supported printers.
3. Make a transaction to get to the receipt view.  You will see a [Print Receipt] button.

Note: CoineyKit does not currently support the Star Micronics SM-L200.

Note: If you plan to implement receipt printing in your own app, do not call `CYEnablePrinting(YES)`, since the printer's `EASession` cannot be shared.

## Submitting Your App for Review

When submitting your app for review through iTunes Connect, you will need an MFi PPID (Made for iPhone Product Plan ID) for interoperation with the Miura M010.  Please use the form [here](../../wiki/PPID-の申請) to request your PPID.

## And that's it!

If you have any further questions feel free to email <coineykit-support@coiney.com>.
