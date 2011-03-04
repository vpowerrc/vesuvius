var Globals = {
	totalRecords : 0,      
	totalResults  : null,  
	searchTerm    : $.trim(document.getElementById("searchBox").value),
	language      : document.getElementById("language").value,
	refreshRate   : 3500, 
	scrollSpeed   : 3000,
	rowPadding    : 18, // # of pixels padding each row
	imagePadding  : 18, // # of pixels padding between images on the same row
	imageBorder   : 4,  // size of the image border in pixels
	headerHeight  : $("#subheader").height() + $("#header").height(), // pixels in height of the header
	footerHeight  : 150,  // pixels in height of the footer
	enableConsole : false,
	nextRow       : 0,
	initDone      : 0,
	uuidSkipList  : new Array("1", "2"), // uuid's to always skip (sahana uuid)
	scrollCount : new Array(-1, -1, -1),
	scrollRightEnd : new Array(0, 0, 0),
	aPerson : [],
	perPage : 25,
	currPage : 1,
	oldCurrPage : 1, // place holder
	maxRows :  Math.ceil(($(window).height()-210)/300) > 4 ? 4 : Math.ceil(($(window).height()-210)/300),
	sortedBy : "",  //default value
	json : "",
	displayMode : true,
	personListOld : [], // old list of persons for comparison
	personList : [], // list of people we WILL download information for
	Q : [],
	Q2 : [],
	incident : $("#disasterList").val(),
	results : [],
	updaterId : null,
	updaterTimer : 60000,  //1min
	doRefresh : true,
	isiPad : false,
	timeElapsed : 0
};



