const app = getApp()
let index = 0
Page({
  data:{
    subject:null,
    current:0,
    total:0,
    cur_id:null,
    cur_tihao:null,
    titles:[],
  },
  onLoad() {
    const db = wx.cloud.database()
    const _ = db.command
    db.collection("myCollection").doc(app.globalData.globalUserid)
    .get().then(res=>{
      // console.log('res',res)
      app.globalData.globalCollectionList = res.data.collectionList
      app.globalData.globalQuestionList = res.data.questionList
      console.log('globalcollection',app.globalData.globalCollectionList)
      console.log('globalquestion',app.globalData.globalQuestionList)
      this.setData({
        total:res.data.collectionList.length,
        current:app.globalData.globalCollectionNum,
        titles:res.data.titles
      })
      this.setData({
        cur_id:res.data.collectionList[this.data.current],
        cur_tihao:res.data.questionList[this.data.current],
      })
      console.log('cur_id',this.data.cur_id)
      console.log('cur_tihao',this.data.cur_tihao)
      const db1 = wx.cloud.database()
     db1.collection("questions").doc(this.data.cur_id)
     .get().then(detail=>{
       console.log('detail',detail)
       this.setData({
         subject:detail.data.question_bank[this.data.cur_tihao]
       })
     })
    })
  

  },

  next(){
    if(this.data.current+1 >= this.data.total){
      wx.showToast({
        icon:"error",
        title: '已经是最后一道题啦'
      })
      return
    }
    else{
      this.setData({
        current : this.data.current + 1,
      })
      this.setData({
        cur_id:app.globalData.globalCollectionList[this.data.current],
        cur_tihao:app.globalData.globalQuestionList[this.data.current]
      })
      const db = wx.cloud.database()
      const _ = db.command
      db.collection("questions").doc(this.data.cur_id)
      .get().then(detail=>{
        console.log('detail',detail)
        this.setData({
          subject:detail.data.question_bank[this.data.cur_tihao]
        })
      })
    }
  },

  pre(){
    if(this.data.current <= 0){
      wx.showToast({
        icon:"error",
        title: '已经是第一道题啦'
      })
      return
    }
    else{
      this.setData({
        current : this.data.current - 1,
      })
      this.setData({
        cur_id:app.globalData.globalCollectionList[this.data.current],
        cur_tihao:app.globalData.globalQuestionList[this.data.current]
      })
      const db = wx.cloud.database()
      const _ = db.command
      db.collection("questions").doc(this.data.cur_id)
      .get().then(detail=>{
        console.log('detail',detail)
        this.setData({
          subject:detail.data.question_bank[this.data.cur_tihao]
        })
      })
    }
  },

  delete(){
    for(var i=0;i<this.data.total;i++){
      if(app.globalData.globalCollectionList[i]==this.data.cur_id&&app.globalData.globalQuestionList[i]==this.data.cur_tihao){
          index = i
          break
      }
    }
    console.log('CollectionList',app.globalData.globalCollectionList)
    app.globalData.globalCollectionList.splice(index,1) 
    app.globalData.globalQuestionList.splice(index,1)
    this.data.titles.splice(index,1)
    console.log('after',app.globalData.globalCollectionList)
    const db = wx.cloud.database()
    const _ = db.command
    db.collection('myCollection').doc(app.globalData.globalUserid).update({
      data:{
          collectionList:app.globalData.globalCollectionList,
          questionList:app.globalData.globalQuestionList,
          titles:this.data.titles,
      }
    })
    this.setData({
      total:this.data.total-1,
      cur_id:app.globalData.globalCollectionList[this.data.current],
      cur_tihao:app.globalData.globalQuestionList[this.data.current]
    })
    db.collection("questions").doc(this.data.cur_id)
    .get().then(detail=>{
      console.log('detail',detail)
      this.setData({
        subject:detail.data.question_bank[this.data.cur_tihao]
      })
    })
  },
})