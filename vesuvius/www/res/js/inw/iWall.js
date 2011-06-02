// iWall v1.6.0 //
// -----------------------------
// v1.0.0 ~ greg original
// v1.0.1 ~ merwan revisions
// v1.1.0 ~ begin using DOM tree manipulations and jquery
// v1.5.0 ~ new views, separated into proper files.
// v1.6.0 ~ filters working, infinite loop bug fixed (xajax not respecting scope)


// used to simulate array functions
Array.prototype.remove = function(from, to) {
	var rest = this.slice((to || from) + 1 || this.length);
	this.length = from < 0 ? this.length + from : from;
	return this.push.apply(this, rest);
};

// called when user starts the application
$(document).ready(function start() {
	Globals.searchMode = $("#searchMode").val(); 
	Globals.sortedBy = Globals.searchMode == "solr" ? "" : "updated";
	Globals.isiPad = window.Touch != undefined;
	window.onorientationchange = function() {
		ScrollView.pause();
		if (!Globals.displayMode && $("#content").css("display") == "none") {
			ScrollView.goFullScreen()
		} else {
			searchSubset();
		}

	}

	
	var doc = document;  
	Globals.initDone = 1; 

    $("#content").css({ paddingRight: "15px", paddingTop: "10px" });
	
	$("#details").hide();
	
	// add an event to monitor when the search box gains focus
	var box = doc.getElementById("searchBox");
	box.onfocus = function() {
		box.style.color = "#000000";
		box.value = box.value == "Enter a name..." ? "" : box.value;
	}
	
	box.onblur = function() {
		box.value = box.value == "" ? "Enter a name..." : box.value;
		if ( box.value == "Enter a name..." )
			box.style.color = "#CCC";
	}

	$("#sortOrderIcon").click(function() { Utils.ascDesc(this) })
					   .css({cursor: "pointer"});
	
	$("#buttonPlay").css("opacity", 0.3);
	$("#buttonPlay").css("filter", "progid:DXImageTransform.Microsoft.Alpha(opacity=30)");

	$("#loadingX").css( {height: Math.round($(window).height() - 190) + "px",
						 paddingTop: Math.round(($(window).height() - 350)/2) + "px"});
	
	Globals.imageHeight = Math.floor(($(window).height() - Globals.headerHeight - Globals.footerHeight - (2*(Globals.rowPadding+Globals.imageBorder))) / Globals.maxRows);
	
	if ( window.location.hash.length > 1 ) { //for bookmarking
		box.style.color = "#000000";
		$("#searchBox").val(unescape(window.location.hash).replace('#', ''));
		searchSubset();
	}
});

function searchSubset() {
	Globals.searchTerms = $.trim($("#searchBox").attr("value"));
	Globals.searchTerms = Globals.searchTerms == "Enter a name..." || Globals.searchTerms == "All" ? "" : Globals.searchTerms;
	
	if ( Globals.searchTerms.length < 2 && Globals.searchMode === "sql" ) {
		alert("Please enter at least 2 characters of a name.");
		return;
	}
	
	var missing   = $("#checkMissing")   .is(":checked"),
		alive     = $("#checkAliveWell") .is(":checked"),
		injured   = $("#checkInjured")   .is(":checked"),
		deceased  = $("#checkDeceased")  .is(":checked"),
		unknown   = $("#checkUnknown")   .is(":checked"),
		found     = $("#checkFound")     .is(":checked"),
		
		complex   = $("#checkSexComplex").is(":checked"),
		male 	  = $("#checkSexMale")   .is(":checked"),
		female 	  = $("#checkSexFemale") .is(":checked"),
		genderUnk = $("#checkSexOther")  .is(":checked"),
		
		child 	  = $("#checkAgeChild")  .is(":checked"),
		adult	  = $("#checkAgeYouth")  .is(":checked"),
		ageUnk    = $("#checkAgeUnknown").is(":checked"),
		
		suburban  = $("#checkSuburban")  .is(":checked"),
		nnmc      = $("#checkNNMC")      .is(":checked"),
		otherHosp = $("#checkOtherHosp") .is(":checked"),

		sStatus       = missing + ";" + alive + ";" + injured + ";" + deceased + ";" + unknown + ";" + found,
		sGender       = complex + ";" + male + ";" + female + ";" + genderUnk,
		sAge          = child + ";" + adult + ";" +	ageUnk,
		sHospital     = suburban + ";" + nnmc + ";" + otherHosp,

		sPageControls = Globals.perPage * (Globals.currPage - 1)  + ";" 
					  + Globals.perPage + ";" 
					  + Globals.sortedBy + ";" 
					  +	Globals.displayMode;
		
		
	Globals.incident = Globals.incident || $("#shortName").val(); 
	Globals.searchMode = $("#searchMode").val();
	$("#updateAlerts, #updateAlerts2").hide();

	inw_getData(Globals.searchMode, Globals.incident, Globals.searchTerms, sStatus, sGender,	sAge, sHospital, sPageControls);
	if ( Globals.searchMode == "sql" ) {
		sPageControls = Globals.perPage * (Globals.currPage)  + ";" 
				  + Globals.perPage + ";" 
				  + Globals.sortedBy + ";" 
				  +	Globals.displayMode;
		if ( Globals.displayMode ) {
			inw_hasNextPage(Globals.searchMode, Globals.incident, Globals.searchTerms, sStatus, sGender,	sAge, sHospital, sPageControls);
			inw_getAllCount(Globals.incident);
		}
		$("#sqlFoundLabel").show();
		$("#solrFoundLabel").hide();
	} else {
		$("#solrFoundLabel").show();
		$("#sqlFoundLabel").hide();
	}

	$("#foundLabel").show();
	if ( Globals.displayMode && Globals.searchMode != "sql" )
		$("#maxShown").hide();
	else 
		$("#maxShown").show();
		
	$("#menuwrap").append($("#searchOptions").css({marginTop: "10px", marginLeft: "5px"}).show());
	if ( !$("#shortName").val().match(/cmax/) ) $("#hospital").hide();
	$("#content").css({marginRight: "0px", paddingRight: "0px"});
	
	if ( Globals.initDone == 1 )
		$("#scrolling_content").html('<div id="loadingX" class="glass"><img src="res/img/loader.gif" /></div>').show(50);
	
}

Object.size = function(obj) {
	var size = 0, key;
	for (key in obj) {
		if (obj.hasOwnProperty(key)) size++;
	}
	return size;
};

function handleUuidListResponse() {
	var temp = [], freshUuids = [];

	$("#totalRecordsSOLR").html(Utils.addCommas($("#totalRecordsSOLR").html()));

	showFacets();
	window.location.hash = Globals.searchTerms;

	if ( Globals.displayMode ) {
		Globals.displayMode = true; 
		DetailsView.drawPage();
	}
	else 
		ScrollView.init();
}

function showFacets() {
	var tempGender = 0,
		tempAge = 0;
		
	if ( Globals.searchMode == "solr" ) {
		var facets = jQuery.parseJSON($("#SOLRFacets").val());
		for( facet in facets ) {
			$("#" + facet + " > span").remove();
			$("#" + facet).append($("<span></span>")
						  .css("font-size", "8pt")
						  .html(" - [" + Utils.addCommas(facets[facet]) + "]"));
			if ( (facet == "male" || facet == "female") && parseInt(facets[facet]) > 0 )
				tempGender++;
			else if ( (facet == "child" || facet == "adult") && parseInt(facets[facet]) > 0 )
				tempAge++;
		}
	} else {
		$("#filtersWrapper").find("label > span").remove();
	}
}



//
// Person Class
//
function Person() {

	// Basically takes the json-derived associative-array and inits fields.
	// Also inits other useful fields.
	this.init =  function(args) {
		if ( args ) {
			var date = Date.parse(args["statusSahanaUpdated"]);
			this.uuid         = args["p_uuid"]; 
			this.encodedUUID  = args["encodedUUID"];
			this.statusSahana = args["opt_status"]; 
			this.name         = $.trim(args["full_name"]) == "unknown unknown" || $.trim(args["full_name"]) == undefined ? "Unknown name" :  $.trim(args["full_name"]) || "Unknown name"; 
			this.age          = args["years_old"] || "N\/A"; 
			this.ageGroup     = !Utils.isNumber(this.age) || this.age < 0 ? "Unknown" : (this.age >= 18 ? "Adult" : "Youth");
			this.statusSahanaUpdated = date.toString("yyyy-MM-dd HH:mm"); 
			this.statusTriage = args["statusTriage"]; 
			this.id           = args["id"]; 
			this.peds         = args["peds"]; 
			this.location     = args["last_seen"]; 
			this.comments     = args["comments"]; 
			this.image        = null;
			this.imageUrl     = args["imageUrl"] || "res/img/s4unknown.png"; 
			this.imageHeight  = parseInt(args["imageHeight"]); 
			this.imageWidth   = parseInt(args["imageWidth"]); 
			this.hospitalIcon = args["hospitalIcon"] || "";
			this.imageShow    = true;
			this.x            = -999999;
			this.y            = -999999;
			this.wipe         = false; 

			if ( args["gender"] === "mal" )
				this.gender = "Male";
			else if ( args["gender"] === "fml" )
				this.gender = "Female";
			else if ( args["gender"] === "cpx" )
				this.gender = "Complex";
			else 
				this.gender = "Unknown";				
			
			this.statusString()
		}
	};
		
		// to implement
	this.equals = function(otherPerson) {
		alert("equals!");
	}
	
	this.statusString = function() {
		var ss = this.statusSahana;
		
		if (this.statusSahana == "mis") {
			this.tagColor         = "00C";
			this.tagRGBA		  = "rgba(220,220,250, 0.60)";
			this.tagClass         = "statusMissing";
			this.statusSahanaFull = "missing";

		} else if (this.statusSahana == "ali") {
			this.tagColor         = "0A0";
			this.tagRGBA		  = "rgba(220,250,220, 0.60)";
			this.tagClass         = "statusAlive";
			this.statusSahanaFull = "alive and well";

		} else if (this.statusSahana == "inj") {
			this.tagColor         = "C00";
			this.tagRGBA		  = "rgba(250,220,220, 0.60)";
			this.tagClass         = "statusInjured";
			this.statusSahanaFull = "injured";

		} else if (this.statusSahana == "dec") {
			this.tagColor         = "000";
			this.tagRGBA		  = "rgba(220,220,220, 0.60)";
			this.tagClass         = "statusDeceased";
			this.statusSahanaFull = "deceased";
		} else if (this.statusSahana == "fnd") {
			this.tagColor         = "802A2A";
			this.tagClass         = "statusFound";
			this.statusSahanaFull = "found";
		} else {
			this.tagColor         = "777";
			this.tagRGBA		  = "rgba(220,220,220, 0.60)";
			this.tagClass         = "statusUnknown";
			this.statusSahanaFull = "unknown";
		}
	};
}
