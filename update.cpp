#include <cstdio>
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

void makePage(string filename, string thumbnail, string YTlink,string description,string time, string movie, string rating, string duration, string IMDbLink)
{
	ofstream pg;
	pg.open(filename.c_str());//filename.c_str()
	pg << "<!doctype html><html lang=\"en\"> <head> <!-- Title --> <title>"+movie+"</title> <!-- GET MDL --> <link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"><link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.2.1/material.indigo-pink.min.css\"><script defer src=\"https://code.getmdl.io/1.2.1/material.min.js\"></script><!-- COLOR --><link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.2.1/material.blue-indigo.min.css\" /><!-- CSS --><link rel=\"stylesheet\" type=\"text/css\" href=\"checkStyle.css\"> <meta charset=\"utf-8\"> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"> <meta name=\"description\" content=\"A front-end template that helps you build fast, modern mobile web apps.\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0\"> <!-- Add to homescreen for Chrome on Android --> <meta name=\"mobile-web-app-capable\" content=\"yes\"> <link rel=\"icon\" sizes=\"192x192\" href=\"images/android-desktop.png\"> <!-- Add to homescreen for Safari on iOS --> <meta name=\"apple-mobile-web-app-capable\" content=\"yes\"> <meta name=\"apple-mobile-web-app-status-bar-style\" content=\"black\"> <meta name=\"apple-mobile-web-app-title\" content=\"Material Design Lite\"> <link rel=\"apple-touch-icon-precomposed\" href=\"images/ios-desktop.png\"> <!-- Tile icon for Win8 (144x144 + tile color) --> <meta name=\"msapplication-TileImage\" content=\"images/touch/ms-touch-icon-144x144-precomposed.png\"> <meta name=\"msapplication-TileColor\" content=\"#3372DF\"> <link rel=\"shortcut icon\" href=\"images/favicon.png\"> <link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Roboto:regular,bold,italic,thin,light,bolditalic,black,medium&amp;lang=en\"> <link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"> <link rel=\"stylesheet\" href=\"$$hosted_libs_prefix$$/$$version$$/material.teal-red.min.css\"> <link rel=\"stylesheet\" href=\"styles.css\"></head> <body> <div class=\"demo-layout mdl-layout mdl-layout--fixed-header mdl-js-layout mdl-color--grey-100\"> <div class=\"demo-ribbon\"></div> <main class=\"demo-main mdl-layout__content\"> <div class=\"demo-container mdl-grid\"> <div class=\"mdl-cell mdl-cell--2-col mdl-cell--hide-tablet mdl-cell--hide-phone\"></div> <div class=\"demo-content mdl-color--white mdl-shadow--4dp content mdl-color-text--grey-800 mdl-cell mdl-cell--8-col\"> <h3>"+movie+"</h3> <iframe width=\"560\" height=\"415\" src=\""+YTlink+"\" frameborder=\"0\" allowfullscreen></iframe> <br /> <img class=\"floatty\" src=\" " +thumbnail+ " \" /> <h4 class=\"onRight\">Rating: "+rating+" | Duration: "+duration+" | Start Time: "+time+"</h4><br /><br /><p class=\"onRight\">Decription:<br />"+description+"</p><br /><br /><a href=\""+IMDbLink+"\" target=\"_blank\"><button class=\"mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent center\"> Learn More</button></a></div> </div></main></div><script src=\"$$hosted_libs_prefix$$/$$version$$/material.min.js\"></script> </body></html>" << endl;
	pg.close();
}

void addCardSimple(string channel, string time, string movie)
{
	cout << "<div class=\"mdl-card mdl-cell mdl-cell--6-col mdl-cell--4-col-tablet mdl-shadow--2dp\"><div class=\"mdl-card__title\"><h1 class=\"mdl-card__title-text\">" + movie + "</h1></div><div class=\"mdl-card__supporting-text\"><p> <strong>" + time + "</strong> <br /> " + channel + " </p></div></div>" << endl;
}

void addCardFull(string target, string thumbnail, string rating, string name, string time, string channel, string description)
{
	cout << "<div class=\"mdl-card mdl-cell mdl-cell--6-col mdl-cell--4-col-tablet mdl-shadow--2dp\"><a href=\""+target+"\"><figure class=\"mdl-card__media\"><img src=\"" + thumbnail + "\" alt=\"\" /></figure></a><div class=\"mdl-card__title\"><h1 class=\"mdl-card__title-text\">"+ name +"</h1><h1 class=\"mdl-card__title-text\">"+rating+"</h1></div><div class=\"mdl-card__supporting-text\"><strong>" + time + "</strong><br /><strong>"+channel+"</strong><p>"+description+"</p></div></div>" << endl;
}

int main()
{
	ifstream fin;
	fin.open("movies.txt");
	ifstream rfin;
	string path = "/home/panos/Desktop/siteUpdates/tipaizei.github.io/moviePages/";
	rfin.open("movieReviews.txt");
	freopen("index.html", "wt", stdout);


	ifstream yt;
	yt.open("movieLinks.txt");
	ifstream imdb;
	imdb.open("imdbLinks.txt");

	// Starting tags
	cout << "<html lang=\"en\"><head><!-- Title --><title>Ti Paizei</title><!-- CSS --><link rel=\"stylesheet\" type=\"text/css\" href=\"style2.css\"><!-- GET MDL --><link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"><link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.2.1/material.indigo-pink.min.css\"><script defer src=\"https://code.getmdl.io/1.2.1/material.min.js\"></script><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body><html lang=\"fr\"><head><!--https://dribbble.com/shots/2001637-Article-News-Card-UIhttp://www.grafikart.fr/tutoriels/html-css/card-ui-629--><meta charset=\"UTF-8\"><link href='http://fonts.googleapis.com/css?family=Open+Sans:400,700' rel='stylesheet' type='text/css'><link rel=\"stylesheet\" href=\"css/style.min.css\"></head><body><div class=\"mdl-layout mdl-js-layout mdl-color--grey-100\"><main class=\"mdl-layout__content\"><div class=\"mdl-grid\">" << endl;

	string movie;
	string channel;
	string time;
	string filename;
	string movieTitle;
	string rating;
	string description;
	string duration;
	string thumbnail;
	string null = "#";

	//Cards

	while(true){
		getline (fin,channel);
		if(channel=="SCRIPT_END")break;
		else{
			getline (fin,time);
			getline (fin,movie);
			getline (rfin, movieTitle);
			if(movieTitle=="None"){
				movieTitle = movie;
				rating = "(?)";
				description = "No Info";
				duration = "?h ?m";
				thumbnail = "http://www.classicposters.com/images/nopicture.gif"; 
				addCardFull(null,thumbnail, rating, movie, time, channel, description);
			}
			else{
				getline (rfin, thumbnail);
				getline (rfin, rating);
				rating = "("+rating+"/10)";
				getline (rfin, duration);
				getline (rfin, description);
				string YTlink;
				yt >> YTlink;
				string IMDbLink;
				imdb >> IMDbLink;
				filename = path + movie + ".html";
				makePage(filename,thumbnail,YTlink,description,time,movie,rating,duration,IMDbLink);
				string target = "../tipaizei.github.io/moviePages/" + url_encode(movie) + ".html";
				addCardFull(target,thumbnail, rating, movie, time, channel, description);
			}
			//addCardSimple(channel, time, movie);
		}
		string blank = "";
		getline(rfin,blank);
		if(blank!="")getline(rfin,blank);
	}

	// IMDb 
	
	addCardFull("http://www.imdb.com/","data:image/png;base64,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", "", "IMDb", "www.imdb.com", "Best Movie Reviews", "All Data is from IMDb. Be sure to check it out for more movie info, reviews and updates.");

	// Ending Tags
	cout << "</div></main></div></body></html>" << endl;


	/*
	while(true){
		string str;
		fin >> str;
		if(str=="SCRIPT_END")break;
		else{
			channel = str;
			getline (fin,time);
			getline (fin,movie);
			cout << str << " - " << time << " - " << movie << endl;
		}
	}
	*/

	fin.close();
	rfin.close();
	yt.close();
	imdb.close();
	return 0;
}

/*
while(true){
		getline (fin,channel);
		if(channel=="SCRIPT_ENDCRIPT_END")break;
		else{
			getline (fin,time);
			getline (fin,movie);
			cout << channel << " - " << time << " - " << movie << endl;
		}
	}
*/