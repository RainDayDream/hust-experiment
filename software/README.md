# 软工

- code_final:实现小程序的全部代码
- design_detail:设计思路和细节
- image：小程序所需要的图片
- 徐雨梦、何佳乐、张若珂、鲍凯琳.pptx：展示的ppt
- 小程序二维码：发布后所有人可以扫描的二维码（2022.12.8之前有效，之后由于数据库不再续费许多功能将无法使用）
- 软件工程报告2022-徐雨梦-何佳乐-鲍凯琳-张若珂：团队报告

## 团队分工

| 成员   | 分工                           | 贡献度 |
| ------ | ------------------------------ | ------ |
| 徐雨梦 | 云函数实现数据库与小程序的交互 | 25%    |
| 何佳乐 | 数据库创建、管理与可视化       | 25%    |
| 鲍凯琳 | “我”界面设计与优化             | 25%    |
| 张若珂 | “题库”和“错题集”界面设计与优化 | 25%    |

## 界面详情

code_final/miniprogram/pages

- collection:收藏的题目列表（展示题目）
- currentErr：做完一套题之后的题目列表包含错了多少道题
- currentErrdetail：展示currentErr题目列表的具体题目
- errorclt：错题集的题目具体展示
- errorlist：错题集集合展示（错题集科目）
- home：首页
- me：个人中心界面
- mytiku：正在刷题的题集的题目详情
- questiondetail：collection的题目列表的具体题目展示
- record：学习报告
- tikuxiaoxue：展示年级列表，可以选择
- tikuxiaoxue1：展示科目列表，可以选择
- tikuxiaoxue1math：展示tikuxiaoxue和tikuxiaoxue1选择后的题集的题目
