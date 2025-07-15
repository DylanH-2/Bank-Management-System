function editAccount() {
  const name = prompt("Enter account name to edit:");
  const account = accounts.find(acc => acc.name === name);

  if (!account) {
    alert("Account not found.");
    return;
  }

  let option = prompt(`Editing ${account.name}\n
1: Change Name
2: Change PIN
3: Reset Balance
0: Cancel
Enter option:`);

  if (option === "1") {
    let valid = false;
    while (!valid) {
      let newName = prompt("Enter new name (letters only):");
      if (/^[A-Za-z]+$/.test(newName)) {
        account.name = newName;
        valid = true;
        alert("Name updated.");
      } else {
        alert("Invalid name. Only letters allowed.");
      }
    }
  } 
  else if (option === "2") {
    let valid = false;
    while (!valid) {
      let newPin = prompt("Enter new 4-digit PIN:");
      if (/^\d{4}$/.test(newPin)) {
        account.pin = newPin;
        valid = true;
        alert("PIN updated.");
      } else {
        alert("Invalid PIN. Must be 4 digits.");
      }
    }
  }
  else if (option === "3") {
    account.balance = 0;
    account.transactions.push({
      type: "Reset",
      amount: 0
    });
    alert("Balance reset to $0.00 and transaction recorded.");
  }
  else if (option === "0") {
    alert("Edit cancelled.");
  }
  else {
    alert("Invalid option.");
  }

  showAccounts();
}
