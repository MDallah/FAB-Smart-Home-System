bool sendEmail()
{
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);

  // For library version 1.2.0 and later which STARTTLS protocol was supported,the STARTTLS will be
  // enabled automatically when port 587 was used, or enable it manually using setSTARTTLS function.
  //smtpData.setSTARTTLS(true);

  // Set the sender name and Email
  smtpData.setSender("FAB-Smart-Home-System", emailSenderAccount);

  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");

  // Set the subject
  smtpData.setSubject(emailSubject);

  // Set the message with HTML format
  sprintf(emailMessage, "<h2>High temperature detected:</h2><br/><p><b>Temperature (°C): <font color='red'>%.2f</font></b></p><br/><p><b>Please check the server room as soon as you can!</b></p><br/><p><b>Have a nice day</p></b><p><b>Your FAB-Smart-Home-System</b></p>", temperature);
  smtpData.setMessage(emailMessage, true);

  // Add recipients
  smtpData.addRecipient(Recipient);

  smtpData.setSendCallback(sendCallback);

  // Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
  {
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
    return false;
  }
  // Clear all data from Email object to free memory
  smtpData.empty();
  return true;
}

// Callback function to get the Email sending status
void sendCallback(SendStatus msg)
{
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success())
  {
    emailSent = true;
    Serial.println("----------------");
  }
  // Reset task-wdt (task watchdog timer).
  esp_task_wdt_reset();
}
