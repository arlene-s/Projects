# Import libraries
import numpy as np
import pandas as pd

# In this section, you can use a search engine to look for the functions that will help you implement the following steps
# Load dataset and show basic statistics
dataset = pd.read_csv('pulsar_stars.csv')

# 1. Show dataset size (dimensions)
print("Dimensions of dataset:", dataset.shape)

# 2. Show what column names exist for the 9 attributes in the dataset
print("Column names:", dataset.columns)

# 3. Show the distribution of target_class column
print("Distribution of the column:", dataset['target_class'].value_counts())

# 4. Show the percentage distribution of target_class column
print("Percent distribution of target_class:", dataset['target_class'].value_counts(normalize=True)*100)


# Separate predictor variables from the target variable (X and y as we did in the class)
X = dataset.iloc[:, :-1]   # every column but target variable column
y = dataset.iloc[:,-1]     # target variable column


# Create train and test splits for model development. Use the 80% and 20% split ratio
# Name them as X_train, X_test, y_train, and y_test
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state=0)


# Standardize the features (Import StandardScaler here)
from sklearn.preprocessing import StandardScaler

sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.fit_transform(X_test)


# Below is the code to convert X_train and X_test into data frames for the next steps
# cols = X_train.columns
X_train = pd.DataFrame(X_train, columns=X.columns) # pd is the imported pandas lirary - Import pandas as pd
X_test = pd.DataFrame(X_test, columns=X.columns) # pd is the imported pandas lirary - Import pandas as pd


# Train SVM with the following parameters.
   #    1. RBF kernel
   #    2. C=10.0 (Higher value of C means fewer outliers)
   #    3. gamma = 0.3
from sklearn.svm import SVC
classifier = SVC(kernel = 'rbf', gamma=0.3, C=10.0, random_state=0)
classifier.fit(X_train, y_train)


# Test the above developed SVC on unseen pulsar dataset samples
#           im assuming when you say "unseen" it wont be in the dataset ???
print(classifier.predict(sc.transform([[0,0,0,0,0,0,0,0]])))


# compute and print accuracy score
from sklearn.metrics import confusion_matrix, accuracy_score
y_pred = classifier.predict(X_test)

print("Accuracy score :", accuracy_score(y_test, y_pred))

# Save your SVC model (whatever name you have given your model) as .sav to upload with your submission
# You can use the library pickle to save and load your model for this assignment
import pickle

with open('pulsarClassifier.sav', 'wb') as file:
    pickle.dump(classifier, file)




# Optional: You can print test results of your model here if you want. Otherwise implement them in evaluation.py file
# Get and print confusion matrix
cm = confusion_matrix(y_test, y_pred)
print(cm)

# Below are the metrics for computing classification accuracy, precision, recall and specificity
TP = cm[0,0]
TN = cm[1,1]
FP = cm[0,1]
FN = cm[1,0]

# Compute Precision and use the following line to print it
precision = TP/(TP+FP)
print('Precision : {0:0.3f}'.format(precision))

# Compute Recall and use the following line to print it
recall = TP/(TP+FN)
print('Recall or Sensitivity : {0:0.3f}'.format(recall))

# Compute Specificity and use the following line to print it
specificity = TN/(TN+FP)
print('Specificity : {0:0.3f}'.format(specificity))
