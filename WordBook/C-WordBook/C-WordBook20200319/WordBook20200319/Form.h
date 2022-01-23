#ifndef _FORM_H
#define _FORM_H

typedef struct _wordBook WordBook;//전방선언

void DisplayMenu();
void DisplayFindMenu(WordBook* wordBook);
void FormFoRecording(WordBook* wordBook);
void FormFoFindingBySpellings(WordBook* wordBook);
void FormFoFindingByMeanings(WordBook* wordBook);
void FormFoCorrecting(WordBook* wordBook);
void FormFoErasing(WordBook* wordBook);
void FormFoArranging(WordBook* wordBook);
void FormFoViewingAll(WordBook* wordBook);

#endif // !_FORM_H
