const app = getApp()
const danxuan = [
  {
    title: '1+1 = ?',
    answer: ['A'],
    options:[
      {
        code:'A',
        option:'2'
      },
      {
        code:'B',
        option:'3'
      },
      {
        code:'C',
        option:'4'
      },
      {
        code:'D',
        option:'5'
      }
    ]
  },
  {
    title: '1+2 = ?',
    answer: ['B'],
    options:[
      {
        code:'A',
        option:'2'
      },
      {
        code:'B',
        option:'3'
      },
      {
        code:'C',
        option:'4'
      },
      {
        code:'D',
        option:'5'
      }
    ]
  }
]
let error = []
Page({

  data: {
    subject:null, //当前的题目
    userSelect:null, //用户选择的选项
    current:1, //当前是第几题
    total:danxuan.length,//总题数
    isSelect: false,
    percent:0,//设置进度条
    rightNum:0,//答对的题数
    falseNum:0,//答错的题数
    totalScore:-1 //总分
  },

  onLoad() {
    const db1 = wx.cloud.database()
    db1.collection('questions').get().then(res=>{
       console.log('res',res)
        let titles = res.data[0].question_bank
        this.setData({
          subject:res.data[0].question_bank[0],
          total:res.data[0].question_bank.length
        })
      })
    // this.setData({
    //   subject:danxuan[0]
    // })
  },

  radioChange(e){
    this.setData({
      userSelect:e.detail.value
    })
  },

  submit(){
    let answer = this.data.subject.answer
    let select = this.data.userSelect

    if(!select){//没做选择
      wx.showToast({
        icon: "none",
        title: '你还没有选择哦'
      })
      return
    }

    if(answer.indexOf(select) > -1){//这道题答对了
      this.setData({
        rightNum:this.data.rightNum + 1
      })
    }
    else{//这道题答错了
      this.setData({
        falseNum:this.data.falseNum + 1
      })
      let subjectNow = this.data.subject
      subjectNow.userSelect = this.data.userSelect
      error.push(subjectNow)
    }

    let current = this.data.current + 1
    
    if(current > danxuan.length){//已经是最后一道题了
      this.setData({
        percent:100
      })
      this.setData({
        totalScore:(this.data.rightNum/danxuan.length*100).toFixed(1)
      })
      wx.showToast({
        icon:'none',
        title: '已经是最后一题啦'
      })
    }
    else{//不是最后一道题，更新题目
      this.setData({
        current:current,
        subject: danxuan[current-1],
        isSelect:false,
        percent:((current-1)/danxuan.length*100).toFixed(2)
      })
    }
  },

  seeError(){
    app.globalData.globalError = error
    //wx.setStorageSync('zrk', error)
    wx.switchTab({//跳转到错题集页面
      url: '/pages/errorclt/errorclt'
    })
  },

  addmytiku(){
    app.globalData.globalMyTiku = danxuan
    wx.showToast({
      title: '添加成功！',
    })
  },

  gohome(){
    wx.switchTab({
      url: '/pages/home/home',
    })
  },

  shoucang(){
    let subjectNow = this.data.subject//获取当前的题目
    //push到数据库(收藏表中对应用户下)
  }
})