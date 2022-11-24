const app = getApp()
let danxuan = []
let error = []
let obtain = 0
let flag=[]
let submit=[]
Page({
  data: {
    Userid:null,
    subject:null, //当前的题目
    userSelect:null, //用户选择的选项
    current:1, //当前是第几题
    total:0,//总题数
    isSelect: false,
    percent:0,//设置进度条
    rightNum:0,//答对的题数
    falseNum:0,//答错的题数
    totalScore:-1, //总分
    Userid:null,
    nums:0,
    kemu:null,
    tiku_id:null,
    havedone:0,
    notSubmit:true,
  },

  onLoad() {
  app.globalData.globalDanxuan = []

  danxuan = []
    const db1 = wx.cloud.database()
    db1.collection('questions').get().then(res=>{
//        console.log('res',res)
      //  console.log('pahse',app.globalData.globalPhase)
      //  console.log('sub',app.globalData.globalSub)
       obtain = app.globalData.globalPhase*3+app.globalData.globalSub
      //  console.log('obtain',obtain)
        danxuan = res.data[obtain].question_bank
        this.setData({
          tiku_id: res.data[obtain]._id,
          subject:res.data[obtain].question_bank[0],
          total:res.data[obtain].question_bank.length,
          Userid:app.globalData.globalUserid,
        })
        for (var i=0;i<this.data.total;i++){ 
          flag[i]=false
          submit[i]=false
        }    
        console.log('flag',flag)
//         console.log('question id:',res.data._id)
      })
    if(app.globalData.globalSub==0){
      this.setData({
        kemu:'chinese'
      })
    }
    else if(app.globalData.globalSub==1){
      this.setData({
        kemu:'math'
      })
    }
    else{
      this.setData({
        kemu:'english'
      })
    }
    db1.collection(this.data.kemu).doc(app.globalData.globalUserid).get().then(
    getnum => {
      this.setData({
        nums:getnum.data.nums
      })
    })
    
  },

  radioChange(e){
    this.setData({
      isSelect:e.detail.value,
      userSelect:e.detail.value
    })
    flag[this.data.current-1]=e.detail.value
    // console.log('value',e.detail.value)
  },

  submit(){
    let answer = this.data.subject.answer
    let select = this.data.isSelect
    if(!select){//没做选择
      wx.showToast({
        icon: "none",
        title: '你还没有选择哦'
      })
      return
    }
    else{
    console.log('user_select',this.data.isSelect)
    danxuan[this.data.current-1].user_select = this.data.userSelect
    console.log('data_select',danxuan[this.data.current-1].user_select)
    console.log('before danxuan',danxuan[0])
    if(answer.indexOf(select) > -1){//这道题答对了
      this.setData({
        rightNum:this.data.rightNum + 1
      })
    }
    else{//这道题答错了
      let subjectNow = this.data.subject
      subjectNow.user_select = this.data.userSelect
      console.log("执行了addtoErr")
      const db = wx.cloud.database()
      const _ = db.command
//       console.log('+1 before',this.data.nums)
      let x = this.data.nums+1
      this.setData({
        falseNum : this.data.falseNum + 1,
        nums : x,
      })
//       console.log('x',x)
//       console.log('+1 after',this.data.nums)
      db.collection(this.data.kemu).doc(app.globalData.globalUserid).update({
        data:{
          errs: _.push(subjectNow),//当前错题添加到错题本
          nums: this.data.nums//错题本数据更新

        },
        success(modify){ 
        console.log('修改成功',modify)
      },
      fail(modify){
        console.log('修改失败',modify)
      }
      })
    }
    if(this.data.current <= this.data.total&&(!submit[this.data.current-1])){
      this.setData({
        havedone:this.data.havedone+1,
        notsubmit:false
      })
      submit[this.data.current-1]=true
    }
    if(this.data.current >= this.data.total){
      wx.showToast({
        icon:"error",
        title: '已经是最后一道题啦'
      })
    }
    else{
      this.setData({
        current:this.data.current+1,
      })
    }
    console.log('havedone',this.data.havedone)
    if(this.data.havedone >= danxuan.length){//做完了
       this.setData({
         percent:100
       })
       this.setData({
         totalScore:(this.data.rightNum/this.data.total*100).toFixed(1)
       })
      console.log('rightnum',this.data.rightNum)
      console.log('totalsocre',this.data.totalScore)
      app.globalData.globalDanxuan =danxuan 
      wx.reLaunch({
          url: '/pages/currentErr/currentErr',
      })
      console.log('danxuan',danxuan)
    }
    else{//还没做完
      this.setData({
      subject: danxuan[this.data.current-1],
      isSelect:flag[this.data.current-1],
      notSubmit:!submit[this.data.current-1],
      percent:((this.data.havedone)/danxuan.length*100).toFixed(2)
      })
    }
  }
 },

  seeError(){
    app.globalData.globalDanxuan =danxuan 
      wx.navigateTo({
      url: '/pages/currentErr/currentErr',
  })
  },

  addmytiku(){
    const db = wx.cloud.database()
    const _ = db.command
    //oPCxW5BjvqKza_bg8mZaJikN2fog
    console.log("app.globalData.globalUserid",app.globalData.globalUserid)
    console.log("app.globalData.globalPhase",app.globalData.globalPhase)
    db.collection("my_questionList").doc(app.globalData.globalUserid).update({
      data:{
        phase:app.globalData.globalPhase,
        subject:app.globalData.globalSub
      }
    })
    console.log('app.globalData.globalSub',app.globalData.globalSub)
    wx.showToast({
          icon: "none",
          title: '已设置为当前题库'
        })
        return
  },
  

  gohome(){
    wx.switchTab({
      url: '/pages/home/home',
    })
  },

  shoucang(){
//     let subjectNow = this.data.subject//获取当前的题目
    //push到数据库(收藏表中对应用户下)
    const db = wx.cloud.database()
    const _ = db.command
//     console.log("id",this.data.tiku_id)
//     console.log("cuerent",this.data.current)
    db.collection("myCollection").doc(app.globalData.globalUserid).update({
      data:{
        collectionList: _.push(this.data.tiku_id),
        questionList: _.push(this.data.current-1),
        titles: _.push(this.data.subject.title)
      }
    })
    wx.showToast({
          icon: "none",
          title: '已添加到我的收藏'
    })
    return
  },
  next(){
    if(this.data.current >= this.data.total){
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
        subject:danxuan[this.data.current-1],
        isSelect:flag[this.data.current-1],
        notSubmit:!submit[this.data.current-1]
      })
    }
  },

  pre(){
    if(this.data.current <= 1){
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
        subject:danxuan[this.data.current-1],
        isSelect:flag[this.data.current-1],
        notSubmit:!submit[this.data.current-1]
      })
    }
  }
})
