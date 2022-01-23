#ifndef _FORM_H
#define _FORM_H
typedef struct _addressBook AddressBook;//전방선언
void DisplayMenu();
void FormFoRecording(AddressBook* addressBook);
void FormFoFinding(AddressBook* addressBook);
void FormFoCorrecting(AddressBook* addressBook);
void FormFoErasing(AddressBook* addressBook);
void FormFoArranging(AddressBook* addressBook);
void FormFoViewingAll(AddressBook* addressBook);
#endif // !_FORM_H
