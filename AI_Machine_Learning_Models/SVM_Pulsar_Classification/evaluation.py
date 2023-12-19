# 1. import any required library to load dataset, open files (os), print confusion matrix and accuracy score
import pickle
import pandas as pd
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

# load dataset
dataset = pd.read_csv('pulsar_stars.csv')
X = dataset.iloc[:, :-1]   # every column but target variable column
y = dataset.iloc[:,-1]     # target variable column

# 2. Create test set if you like to do the 80:20 split programmatically or if you have not already split the data at this point
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state=0)

# normalize
sc = StandardScaler()
X_test = sc.fit_transform(X_test)

X_test = pd.DataFrame(X_test, columns=X.columns)

# 3. Load your saved model for pulsar classifier that you saved in pulsar_classification.py via Pikcle
with open('pulsarClassifier.sav', 'rb') as file:
    classifier = pickle.load(file)

# 4. Make predictions on test_set created from step 2
y_pred = classifier.predict(X_test)

# 5. use predictions and test_set (X_test) classifications to print the following:
#    1. confution matrix, 2. accuracy score, 3. precision, 4. recall, 5. specificity
#    You can easily find the formulae for Precision, Recall, and Specificity online.

# Get and print confusion matrix
cm = confusion_matrix(y_test, y_pred)
print(cm)

# Below are the metrics for computing classification accuracy, precision, recall and specificity
TP = cm[0,0]
TN = cm[1,1]
FP = cm[0,1]
FN = cm[1,0]

# compute and print accuracy score
accuracy = (TP+TN)/(TP+FP+FN+TN)
print('Accuracy: {0:0.3f}'.format(accuracy))

# Compute Precision and use the following line to print it
precision = TP/(TP+FP)
print('Precision : {0:0.3f}'.format(precision))

# Compute Recall and use the following line to print it
recall = TP/(TP+FN)
print('Recall or Sensitivity : {0:0.3f}'.format(recall))

# Compute Specificity and use the following line to print it
specificity = TN/(TN+FP)
print('Specificity : {0:0.3f}'.format(specificity))
