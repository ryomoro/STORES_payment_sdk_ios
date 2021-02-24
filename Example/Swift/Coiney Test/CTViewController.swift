import UIKit
import CoineyKit

class CTViewController: UIViewController {
    
    // MARK: - Properties
    
    @IBOutlet weak var memoTextField: UITextField!
    @IBOutlet weak var priceTextField: UITextField!
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        CYKit.prepare(in: self)
    }
    
    // MARK: - IB Actions
    
    @IBAction func makePayment(_ sender: UIButton)
    {
        guard let amountString = priceTextField.text,
              let amount = Int64(amountString),
              amount > 0 else {
            return
        }
        memoTextField.resignFirstResponder()
        priceTextField.resignFirstResponder()

        let memo = memoTextField.text ?? ""
        
        // Create an instance of the Coiney payment controller.
        let coineyController = CYCoineyViewController.init(amount: amount, memo: memo)
        coineyController.delegate = self
        
        // Present it on top of the current controller.
        self.present(coineyController, animated: true, completion: nil)
    }
    
    @IBAction func deauthenticate(_ sender: UIButton)
    {
        memoTextField.resignFirstResponder()
        priceTextField.resignFirstResponder()
        CYAuthenticationViewController.deauthenticate()
    }

    // Private methods
    
    @objc private func done() {
        self.dismiss(animated: true, completion: nil)
    }
    
    private func convertTransaction(transaction: CYTransaction) {
        switch transaction {
        case let creditCardTransaction as CYCreditCardTransaction:
            print("\(creditCardTransaction)")
        case let wechatPayTransaction as CYWechatPayTransaction:
            print("\(wechatPayTransaction)")
        case let emoneyTransaction as CYEmoneyTransaction:
            print("\(emoneyTransaction)")
        default:
            break
        }
    }
    
    private func lookUpTransaction(transactionId: String) {
        CYLookUpTransaction(transactionId) { (transaction, error) in
            guard let transaction = transaction else {
                print("Transaction ID \(transactionId) doesn't exist! Wrong account, maybe? error = \(String(describing: error))")
                return
            }
            self.convertTransaction(transaction: transaction)
        }
    }

    private func lookUpEmoneyTransaction(transactionId: String) {
        CYLookUpEmoneyTransaction(transactionId) { (transaction, error) in
            guard let transaction = transaction else {
                print("Transaction ID \(transactionId) doesn't exist! Wrong account, maybe? error = \(String(describing: error))")
                return
            }
            self.convertTransaction(transaction: transaction)
        }
    }
}

extension CTViewController : CYCoineyViewControllerDelegate {
    
    func coineyViewController(_ aController: CYCoineyViewController,
                              didComplete aTransaction: CYTransaction)
    {
        print("Completed transaction: \(aTransaction)")
        
        if aTransaction is CYEmoneyTransaction {
            self.lookUpEmoneyTransaction(transactionId: aTransaction.identifier)
        } else {
            self.lookUpTransaction(transactionId: aTransaction.identifier)
        }
        
        self.dismiss(animated: true, completion: {
            let transactionViewController = CYTransactionViewController.init(transaction: aTransaction,
                                                                             allowRefunding: true)
            
            transactionViewController.navigationItem.rightBarButtonItem =
                UIBarButtonItem.init(barButtonSystemItem: .done,
                                     target: self,
                                     action: #selector(self.done))
            
            let navigationController = UINavigationController.init(rootViewController: transactionViewController)
            navigationController.modalPresentationStyle = .formSheet
            self.present(navigationController, animated: true, completion: nil)
        })
    }
    
    func coineyViewControllerDidCancel(_ aController: CYCoineyViewController)
    {
        self.dismiss(animated: true, completion: nil)
    }

    func coineyViewController(_ aController: CYCoineyViewController,
                              didCompleteWithUnconfirmedTransaction aTransaction: CYTransaction)
    {
        self.dismiss(animated: true, completion: nil)
    }
}
