﻿#NFA构造同样的文法#

1.	对于NFA每个状态i,创建一个非终结符号A
2.	对于状态i，如果有符号a到状态j的转义，就创建Ai->aAj.如果输入∈达到状态j就创建Ai->Aj
3.	如果i是接受状态就创建Ai->&epsilon;
4.	如果i是自动机开始符号就令Ai为文法的开始符号


#消除左递归#

对于非终结符号A1,A2,A3...An

	for(从1到n每个i){
		for(从1到i-1每个j){
			将每个形如Ai -> Ajγ的产生式替换为产生式组Ai -> δ1γ | δ2γ.... | δkγ
			其中Aj -> δ1 | δ2 | δ3 ... | δk是Aj的产生式 
		}
		消除Aj的立即左递归
	}

#A -> &alpha;B 或者 A -> &alpha;B&beta;并且&epsilon; &isin; &beta;#
则follow(A) &isin; follow(B)
因为如果要应用B的推倒式，那么肯定得和开始字符匹配

例如A -> aA'
	A' -> b | c

abaab

对于第三个a要匹配A'肯定要符合下来是b|c才会应用这个文法
