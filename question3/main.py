import tensorflow as tf
import numpy as np

tf.set_random_seed(1)
np.random.seed(1)

X_train = np.loadtxt('./train_data.txt', skiprows=1, dtype=float)
y_train = np.loadtxt('./train_truth.txt', skiprows=1, dtype=float)

x_test = np.loadtxt('./test_data.txt', skiprows=1, dtype=float)
print(X_train.shape)
print(X_train)
print(y_train.shape)

in_units = 3
h1_units = 4
h2_units = 4
n_epoch = 2000
lr = 0.05

x = tf.placeholder(tf.float32, [None, in_units])
y = tf.placeholder(tf.float32, [None, 1])

W1 = tf.Variable(tf.truncated_normal([in_units, h1_units], stddev=0.1))
b1 = tf.Variable(tf.zeros([h1_units]))
W2 = tf.Variable(tf.truncated_normal([h1_units, h2_units], stddev=0.1))
b2 = tf.Variable(tf.zeros([h2_units]))
W3 = tf.Variable(tf.zeros([h2_units, 1]))
b3 = tf.Variable(tf.zeros([1]))

hidden1 = tf.nn.relu(tf.add(tf.matmul(x, W1), b1))
hidden2 = tf.nn.relu(tf.add(tf.matmul(hidden1, W2), b2))
y_pred = tf.add(tf.matmul(hidden2, W3), b3)

loss = tf.reduce_mean((y_pred - y) ** 2)
op = tf.train.AdamOptimizer(lr).minimize(loss)

y_mean = tf.reduce_mean(y)
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    for epoch in range(n_epoch):
        _, loss_ = sess.run([op, loss], feed_dict={x: X_train, y: y_train.reshape([-1, 1])})
        if epoch % 100 == 0:
            print(f'epoch:{epoch}, loss:{loss_}')

    y_test_pred = sess.run(y_pred, feed_dict={x: x_test})
    print(y_test_pred.shape)
    print(y_test_pred)
    with open('test_predicted.txt', 'w') as f:
        f.write('y\n')
        for items in y_test_pred:
            f.write(str(items[0])+'\n')
        f.close()