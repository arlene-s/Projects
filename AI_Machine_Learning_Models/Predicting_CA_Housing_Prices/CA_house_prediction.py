import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns

# load dataset
data = pd.read_csv("housing.csv")

# want to predict median_house_value (target variable)

# cannot directly feed into network: ocean_proximity bc its text

# some missing values, drop nan entries
# save in data object
data.dropna(inplace=True)

# split data into training and testing data (x and y data)
# train model on one set of data and evaulate on another set
# not going to work on all data, need some unseen data that model never seen before to see if model performs well on this data

from sklearn.model_selection import train_test_split

# 'X' is data frame without target variable
X = data.drop(['median_house_value'], axis=1)   # 'axis=1' dropping a column
# 'y' is only going to be the target variable
y = data['median_house_value']

# 20% of data reserved for evaluating. not being touched
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# join X and y training data to analyze coorelations
train_data = X_train.join(y_train)

#train_data.hist(figsize=(15,8))

# visualize coorelation matrix
# plt.figure(figsize=(15,8))
# sns.heatmap(train_data.corr(), annot=True, cmap="YlGnBu")
# plt.show()

# see what distribution looks like, apply log for a gaussian distribution
train_data['total_rooms'] = np.log(train_data['total_rooms'] + 1)
train_data['total_bedrooms'] = np.log(train_data['total_bedrooms'] + 1)
train_data['population'] = np.log(train_data['population'] + 1)
train_data['households'] = np.log(train_data['households'] + 1)


# print(train_data.ocean_proximity.value_counts())

# for each value in the collumn, set a boolean
# 'get_dummies' one hot encoding
train_data = train_data.join(pd.get_dummies(train_data.ocean_proximity)).drop(['ocean_proximity'], axis=1)

# visualize with scatter plot, houses near the coast are more expensive
# plt.figure(figsize=(15,8))
# sns.scatterplot(x="latitude", y="longitude", data=train_data, hue="median_house_value", palette="coolwarm")
# plt.show()

# how many of the rooms are bedrooms?
train_data['bedroom_ratio'] = train_data['total_bedrooms'] / train_data['total_rooms']

# if you have a block with more households than usual, you will probably also have more rooms, so rooms don't give a full picture
# 'household_rooms' how many rooms per household
train_data['household_rooms'] = train_data['total_rooms'] / train_data['households']


# train multiple models
from sklearn.linear_model import LinearRegression
# scale data
from sklearn.preprocessing import StandardScaler

scaler = StandardScaler()

# split again with new features
X_train, y_train = train_data.drop(['median_house_value'], axis=1), train_data['median_house_value']
X_train_s = scaler.fit_transform(X_train)

reg = LinearRegression()

reg.fit(X_train_s, y_train)

# no hypertuning, just evaluate 
test_data = X_test.join(y_test)

test_data['total_rooms'] = np.log(test_data['total_rooms'] + 1)
test_data['total_bedrooms'] = np.log(test_data['total_bedrooms'] + 1)
test_data['population'] = np.log(test_data['population'] + 1)
test_data['households'] = np.log(test_data['households'] + 1)

test_data = test_data.join(pd.get_dummies(test_data.ocean_proximity)).drop(['ocean_proximity'], axis=1)

test_data['bedroom_ratio'] = test_data['total_bedrooms'] / test_data['total_rooms']
test_data['household_rooms'] = test_data['total_rooms'] / test_data['households']

X_test, y_test = test_data.drop(['median_house_value'], axis=1), test_data['median_house_value']
X_test_s = scaler.transform(X_test)

print("Perfomance of Linear Regression model: ", reg.score(X_test_s, y_test))


# random forest regressor (more powerful, with hyperparameter tuning)
# combine decision trees
from sklearn.ensemble import RandomForestRegressor

forest = RandomForestRegressor()

forest.fit(X_train_s, y_train)

print("Performance of Forest model: ", forest.score(X_test_s, y_test))

# get optimal model
from sklearn.model_selection import GridSearchCV

forest = RandomForestRegressor()

# perform cross evaluation with combinations
param_grid = {
    "n_estimators": [100, 200, 300],
    "min_samples_split": [2, 4],
    "max_depth": [None, 4, 8]
}

grid_search = GridSearchCV(forest, param_grid, cv=5, scoring="neg_mean_squared_error", return_train_score=True)
grid_search.fit(X_train_s, y_train)

best_forest = grid_search.best_estimator_
print("Performance of optimal Forest model: ", best_forest.score(X_test_s, y_test))


