#!/usr/bin/python3

import os
import sys
import numpy as np
import cv2



if __name__ == '__main__':

    WK_DIR = os.path.abspath(os.path.dirname(sys.argv[0]))

    os.chdir(WK_DIR + '/../')

    numbers = [0 for i in range(0, 10)]

    train_csv = open('data/train.csv').readlines()[1:]



    os.system('rm -rf data/timg')

    for train_num in train_csv:

        data = train_num.split('\n')[0].split(',')

        img = np.ones((28, 28), dtype=np.uint8)

        cnt = 0
        for i in range(0, 28):
            for j in range(0, 28):
                img[i, j] = int(data[i * 28 + j + 1])

        label = int(data[0])

        num_dir = 'data/timg/' + str(label)
        if not os.path.lexists(num_dir):
            os.makedirs(num_dir)

        num_file = num_dir + '/' + str(label) + '_' + str(numbers[label]) + '.jpg'
        numbers[label] += 1
        cv2.imwrite(num_file, img)




    train_txt = open('data/train.txt', 'w')

    test_txt = open('data/test.txt', 'w')

    for i in range(0, 10):
        train_cnt = int(1.0 * numbers[i] / 10 * 7)
        for j in range(0, train_cnt):
            num_file = 'data/timg/' + str(i) + '/' + str(i) + '_' + str(j) + '.jpg'
            train_txt.write(num_file + ' ' + str(i) + '\n')
        for j in range(train_cnt, numbers[i]):
            num_file = 'data/timg/' + str(i) + '/' + str(i) + '_' + str(j) + '.jpg'
            test_txt.write(num_file + ' ' + str(i) + '\n')


    pred_csv = open('data/test.csv').readlines()[1:]

    os.system('rm -rf data/pimg')

    cnt = 0

    for pred_num in pred_csv:

        data = pred_num.split('\n')[0].split(',')

        img = np.ones((28, 28), dtype=np.uint8)

        for i in range(0, 28):
            for j in range(0, 28):
                img[i, j] = int(data[i * 28 + j])

        num_dir = 'data/pimg/'
        if not os.path.lexists(num_dir):
            os.makedirs(num_dir)

        num_file = num_dir + '/pred' + str(cnt) + '.jpg'
        cnt += 1

        cv2.imwrite(num_file, img)


