import UIKit
import CoineyKit

class CTViewController: UIViewController {
    
    // MARK: - Properties
    
    @IBOutlet weak var productNameField: UITextField!
    @IBOutlet weak var productPriceField: UITextField!
    
    // MARK: - IB Actions
    
    @IBAction func makePayment(_ sender: UIButton)
    {
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
    
    @IBAction func deauthenticate(_ sender: UIButton)
    {
        CYAuthenticationViewController.deauthenticate()
    }
}

extension CTViewController : CYCoineyViewControllerDelegate {
    
    func coineyViewController(_ aController: CYCoineyViewController!,
                              didComplete aTransaction: CYTransaction!)
    {
        print("Completed transaction: \(aTransaction)")
        
        self.dismiss(animated: true, completion: {
            guard let transactionViewController =
                CYTransactionViewController.init(transaction: aTransaction, allowRefunding: true) else {
                    fatalError("Failed to initialize CYTransactionViewController.")
            }
            
            transactionViewController.navigationItem.rightBarButtonItem =
                UIBarButtonItem.init(barButtonSystemItem: .done,
                                     target: self,
                                     action: #selector(self.coineyViewControllerDidCancel(_:)))
            
            let navigationController = UINavigationController.init(rootViewController: transactionViewController)
            navigationController.modalPresentationStyle = .formSheet
            self.present(navigationController, animated: true, completion: nil)
        })
    }
    
    func coineyViewControllerDidCancel(_ aController: CYCoineyViewController!)
    {
        self.dismiss(animated: true, completion: nil)
    }
}
