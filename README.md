this is oss team project group 9

» What does this project do?

    이 parser는 환자 정보 시스템 parser로 환자들의 명단에서 필요한 정보를 parsing할 수 있게 한 parser 입니다.
    
» Why is this project useful?

    http://www.koreahealthlog.com/news/articleView.html?idxno=23096 
    이 기사에 따르면 진료 정보 기록을 의료기관들끼리 공유해 환자 진료의 연속성을 돕는 사업이 발달하고 있다는 것을 알 수 있습니다. 
    진료 정보 교류사업은 환자 동의를 거쳐 컴퓨터단층촬영(CT)이나 자기공명영상(MRI) 등 영상 정보와 진단·투약 등 진료 기록을 의료기관들끼리
    공유해 환자 진료의 연속성을 돕는 사업이며 이로 인해 중복 촬영이나 검사 등을 최소화해 환자 의료비용 절감에 기여하고 있다는 평가가 있습니다. 
    따라서 저희가 만든 파서 또한 유용할 것으로 예상됩니다.
    
» How do I get started?
    제일 먼저 아이디와 비밀 번호를 입력합니다. (저희는 임의로 id: doctor, pw: 1234로 지정해 주었습니다.)
    이렇게 로그인하면 다섯 개의 메뉴가 있는 것을 볼 수 있습니다.
    1. Basic View: Result of Parsing
        -  json 파일을 파싱한 결과를 보여줍니다.
        
    2. A list of Patients
        -   json 파일에서 환자의 명단을 보여줍니다.
        
    3. My Patients
        -   의사의 name을 입력하면 해당 의사의 환자 명단을 보여줍니다.
        
    4. Patient Who Needs Care
        -   환자들 중 혈압이 140 이상이거나 100이하인 환자들의 명단을 보여줍니다.
        
    5. Exit
    
» Where can I get more help, if I need it?
    저희조는 token을 배열로 관리하였는데 동적메모리 할당을 사용하여 token을 관리하는 법을 배우고 싶습니다. 
