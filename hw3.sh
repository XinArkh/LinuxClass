#! /bin/bash
# filename:hw3
echo -n "��Ҫ���뼸��������"
read num
# �򵥴ֱ��ض���һ�������ֵ��max�͡���Сֵ��min
# ����������������Χ������Ч��
max=-999999999999999999999999
min=999999999999999999999999
sum=0
sort=()
i=1
while ((i<=num))
do
	sort[$i]=999999999999999999999999
	i=$((i+1))
done
i=1
# ���num��until����ѭ����ÿ������һ��������������Ӧ����
until ((i>num))
do
	echo -n "�������$i��������"
	read n
	# ��ȡ���ֵ
	if ((n>max)); then
		max=$n
	fi
	# ��ȡ��Сֵ
	if ((n<min)); then
		min=$n
	fi
	# ��ȡ�ܺ�
	sum=$((sum+n))
	#### ������������������� ####
	j=1
	while ((j<=i))
	do
		if ((n<sort[$j])); then
			break
		fi
		j=$((j+1))
	done
	ii=$i
	while ((ii>j))
	do
		sort[$ii]=$((sort[$ii-1]))
		ii=$((ii-1))
	done
	sort[$j]=$n
	#############################
	i=$((i+1))
done
echo "���ֵ��"$max
echo "��Сֵ��"$min
echo "�ܺ�Ϊ"$sum
echo -n "��С��������"${sort[*]}
echo
