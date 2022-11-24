const app = getApp()
let danxuan = []
let error = []
let obtain = 0
Page({
  data: {
    Userid:null,
    subject:null, //当前的题目
    userSelect:null, //用户选择的选项
    current:1, //当前是第几题
    total:0,//总题数
    isSelect: false,
    Userid:null,
    nums:0,
    question:'',
    num:0
  },

  onLoad() {
    const db1 = wx.cloud.database()
    db1.collection('myCollection').doc(app.globalData.globalUserid).get().then(res=>{
       console.log('res',res)
      danxuan = res.data.titles
      this.setData({
        question:res.data.titles,
        total:res.data.titles.length
      })
    })
  },
   question(e){
     console.log(e.currentTarget.dataset.index); //我是固定参数
     app.globalData.globalCollectionNum=e.currentTarget.dataset.index
     wx.navigateTo({
       url: '/pages/questiondetail/questiondetail',
     })
     },
    collectNULL(){
      wx.navigateTo({
        url: '/pages/mytiku/mytiku',
      })
    }
  
})