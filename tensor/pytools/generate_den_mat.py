import numpy as np

rows = 20000
cols = 20000

# 生成正太分布的值
arr = np.random.randn(rows,cols)
        # print(num[i, j])

with open('densematrix.mtx', 'w') as f:
    f.write('%d %d\n' % (rows,cols))

    for i in range(rows):
        for j in range(cols):
            f.write('%f ' % arr[i, j])
        f.write('\n')
    # for key, values in arr:



# f = open(output, 'w')

# f.write('%d\n' % ndims)
# f.write('\t'.join(map(str, dims)))
# f.write('\n')


# save_arr = np.insert(arr,0,[2,rows,col],axis=0)
# numpy.savetxt('matrix.txt',fmt="%d", save_arr)
