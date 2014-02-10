# Coiney URL Scheme

Action | Parameter                | Value Description | Required? | Notes
------ | ------------------------ | ----------------- | --------- | -----------
`pay`  | `amount`                 | integer           | **Yes**   |
 …     | `currency`               | ISO currency code | **Yes**   | Currently only `jpy` is supported
 …     | `callback_url`           | Escaped URL       | No        | On completion of a transaction the url will be opened, and with query parameters containing transaction information
`open` | `transaction_identifier` | integer           | **Yes**   |
 …     | `callback_url`           | Escaped URL       | No        | Opened when the user dismisses the transaction |


## Payment Example
	coiney://pay?amount=5120&currency=jpy&callback_url=my-app://transaction_complete

### On Successful completion:
	my-app://transaction_complete?status=success&transaction_identifier=abcdefg&approval_code=123

### On Failure:
	my-app://transaction_complete?status=failure


## Transaction Detail Example
	coiney://open?transaction_identifier=abcdefg&callback_url=my-app://closed_transaction