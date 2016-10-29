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
	string path = "/home/panos/Desktop/MoviesSite/moviePages/";
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
				thumbnail = "http://www.cost-ic0803.org/fotografie/foto4.jpg";
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